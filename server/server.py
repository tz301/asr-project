#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/03
"""Deploy."""
import logging
import time
from pathlib import Path

from flask import Flask, redirect, render_template, request, url_for
# pylint: disable=import-error
from utils import ASR_IP, get_pcm_data_list, init_socket, send_data, TEST_WAV
from werkzeug.utils import secure_filename

app = Flask(__name__)

__ALLOWED_EXTENSIONS = {'.wav'}

SOCKET = init_socket(ASR_IP)

TRX = ''
IDX = 0
PCM_DATA = []
AISHELL_TRX = ''
AISHELL_IDX = 0
AISHELL_PCM_DATA = get_pcm_data_list(TEST_WAV)


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


def __allowed_file(filename):
  """If file is supported.

  Args:
    filename: file name.

  Returns:
    If file is supported.
  """
  return Path(filename).suffix in __ALLOWED_EXTENSIONS


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
  if 'file' not in request.files:
    logging.warning(f'file field not found: {request.files}.')
    return __render('index.html', AISHELL_TRX, TRX)

  logging.info('Receive file.')
  file = request.files['file']
  if file and __allowed_file(file.filename):
    time_format = "%Y-%m-%d-%H-%M-%S"
    cur_time = time.strftime(time_format, time.localtime())
    filename = Path(secure_filename(file.filename))
    filename = f'{filename.stem}-{cur_time}{filename.suffix}'
    audio_path = app.config['UPLOAD_FOLDER'] / filename
    file.save(audio_path)
    logging.info(f'Save file to {audio_path}.')
    PCM_DATA = get_pcm_data_list(audio_path)
    return redirect(url_for('recognize'))

  return __render('index.html', AISHELL_TRX, TRX)


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
  global TRX, AISHELL_TRX  # pylint: disable=global-statement
  TRX, AISHELL_TRX = '', ''
  return redirect(url_for('home'))


@app.route('/')
def home():
  """Home."""
  return __render('index.html', AISHELL_TRX, TRX)


def __main():
  """Main function."""
  storage_dir = Path('storage')
  storage_dir.mkdir(exist_ok=True)
  app.config['UPLOAD_FOLDER'] = storage_dir
  app.config['MAX_CONTENT_LENGTH'] = 10 * 1024 * 1024
  app.run(host='0.0.0.0', port='9000')


if __name__ == '__main__':
  logging.basicConfig(format='%(asctime)s %(name)s %(levelname)s %(message)s',
                      level=logging.INFO)
  __main()
