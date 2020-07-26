#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/03
"""Deploy."""
import logging
import time
from argparse import ArgumentParser
from pathlib import Path

import ffmpeg
from flask import Flask, redirect, render_template, request, url_for
from werkzeug.utils import secure_filename

# pylint: disable=import-error
from utils import asr_ip, get_pcm_data_list, init_socket, send_data, TEST_WAV

app = Flask(__name__)
SOCKET = None

TRX = ''
IDX = 0
PCM_DATA = []
AISHELL_TRX = ''
AISHELL_IDX = 0
AISHELL_PCM_DATA = get_pcm_data_list(TEST_WAV)


def __convert_wav(in_audio, out_wav):
  """Using ffmpeg to convert audio to 16k, mono, pcm.

  Args:
    in_audio: input audio file.
    out_wav: output wav file.

  Returns:
    msg, no msg means succeed.
  """
  param = {'fflags': '+bitexact', 'flags:v': '+bitexact',
           'flags:a': '+bitexact', 'map_metadata': '-1'}

  try:
    (ffmpeg.input(str(in_audio))
     .output(filename=str(out_wav), ar=16000, ac=1, acodec='pcm_s16le', **param)
     .global_args("-ignore_unknown", "-vn")
     .run(capture_stdout=True, capture_stderr=True))
  except ffmpeg.Error as ex:
    return ex.stderr.decode('utf-8')
  else:
    return ''


def __render(html, aishell_trx='', trx='', stop_aishell=1, stop_asr=1):
  """Render template.

  Args:
    html: html.
    aishell_trx: transcript for aishell recognize.
    trx: transcript for upload file recognize.
    stop_aishell: if aishell recognize stop.
    stop_asr: if upload file recognize stop.

  Returns:
    Render template.
  """
  base_trx = '识别结果: '
  aishell_trx = base_trx + aishell_trx
  trx = base_trx + trx
  return render_template(html, aishell_trx=aishell_trx, trx=trx,
                         stop_aishell=stop_aishell, stop_asr=stop_asr)


def __asr(pcm_data_list, index):
  """asr.

  Args:
    pcm_data_list: pcm_data_list.
    index: index of pcm data.

  Returns:
    if recognize stop, new index of pcm data and transcript.
  """
  begin_time = time.time()
  while True:
    trx = send_data(SOCKET, pcm_data_list[index])
    if index == len(pcm_data_list) - 1:
      index, stop = 0, 1
      break
    index, stop = index + 1, 0

    if time.time() - begin_time > 0.1:
      break
  return stop, index, trx


def __aishell_asr():
  """Aishell online asr."""
  global AISHELL_IDX, AISHELL_TRX  # pylint: disable=global-statement
  stop, AISHELL_IDX, AISHELL_TRX = __asr(AISHELL_PCM_DATA, AISHELL_IDX)
  return stop


def __online_asr():
  """Online asr for upload file."""
  global IDX, TRX  # pylint: disable=global-statement
  stop, IDX, TRX = __asr(PCM_DATA, IDX)
  return stop


@app.route('/upload', methods=['POST'])
def upload_file():
  """Upload file."""
  global PCM_DATA  # pylint: disable=global-statement
  try:
    if 'file' not in request.files:
      logging.warning(f'file field not found: {request.files}.')
      return __render('index.html', AISHELL_TRX, TRX)

    file = request.files['file']
    if file:
      time_format = "%Y-%m-%d-%H-%M-%S"
      cur_time = time.strftime(time_format, time.localtime())
      filename = Path(secure_filename(file.filename))
      filename = f'test-{cur_time}{filename.suffix}'
      audio_path = app.config['UPLOAD_FOLDER'] / filename
      file.save(audio_path)
      logging.info(f'Save file to {audio_path}.')

      wav_path = app.config['UPLOAD_FOLDER'] / f'{Path(filename).stem}-pcm.wav'
      msg = __convert_wav(audio_path, wav_path)
      if not msg:
        logging.info(f'Convert to {wav_path}.')
        PCM_DATA = get_pcm_data_list(wav_path)
        return redirect(url_for('recognize'))

      logging.error(f'Error: {wav_path}, {msg}.')
      return __render('index.html', AISHELL_TRX, msg, stop_asr=1)
    return __render('index.html', AISHELL_TRX, TRX)

  except Exception as ex:  # pylint: disable=broad-except.
    logging.error(ex)
    return __render('index.html', AISHELL_TRX, str(ex), stop_asr=1)


@app.route('/aishell', methods=['GET', 'POST'])
def aishell():
  """Test aishell wav."""
  if __aishell_asr():
    return redirect(url_for('home'))
  return __render('index.html', AISHELL_TRX, TRX, stop_aishell=0)


@app.route('/recognize', methods=['GET', 'POST'])
def recognize():
  """Recognize wav."""
  if __online_asr():
    return redirect(url_for('home'))
  return __render('index.html', AISHELL_TRX, TRX, stop_asr=0)


@app.route('/reset', methods=['POST'])
def reset():
  """Reset."""
  global IDX, TRX, AISHELL_IDX, AISHELL_TRX  # pylint: disable=global-statement
  IDX, AISHELL_IDX = 0, 0
  TRX, AISHELL_TRX = '', ''
  return redirect(url_for('home'))


@app.route('/')
def home():
  """Home."""
  return __render('index.html', AISHELL_TRX, TRX)


def __main():
  """Main function."""
  parser = ArgumentParser(description="Test asr server.")
  parser.add_argument("asr_port", type=int, help="asr server port.")
  parser.add_argument("port", type=int, help="server port for depoly.")
  args = parser.parse_args()

  global SOCKET  # pylint: disable=global-statement
  SOCKET = init_socket(asr_ip(args.asr_port))

  storage_dir = Path('storage')
  storage_dir.mkdir(exist_ok=True)
  app.config['UPLOAD_FOLDER'] = storage_dir
  app.config['MAX_CONTENT_LENGTH'] = 20 * 1024 * 1024
  app.run(host='0.0.0.0', port=f'{args.port}')


if __name__ == '__main__':
  logging.basicConfig(format='%(asctime)s %(name)s %(levelname)s %(message)s',
                      level=logging.INFO)
  __main()
