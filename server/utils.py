#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/24
"""utils."""
import wave
from pathlib import Path

import zmq

ASR_IP = 'tcp://localhost:6557'
TEST_WAV = Path(__file__).absolute().parent.parent / 'tests/test.wav'


def get_pcm_data_list(wav_file):
  """Get pcm data list, which is split by 200ms.

  b'0' means finish recognize, add extra b'0' before to ensure restart asr.

  Args:
    wav_file: wav file.

  Returns:
    pcm data list.
  """
  if wav_file.read_bytes()[36:40] != b'data':
    raise ValueError(f"{wav_file}: not supported format.")

  with wave.open(str(wav_file), "rb") as file:
    params = file.getparams()
    data = file.readframes(params[3])
  sample_rate = params[2]

  chunk = int(sample_rate * 2 * 0.2)  # 200ms.
  pcm_data_list = [data[i:i + chunk] for i in range(0, len(data), chunk)]
  if pcm_data_list:
    pcm_data_list[-1] += b'0'
  return [b'0'] + pcm_data_list


def init_socket(host):
  """Init socket.

  Args:
    host: host.

  Returns:
    socket.
  """
  context = zmq.Context()
  socket = context.socket(zmq.REQ)  # pylint: disable=no-member
  socket.connect(host)
  send_data(socket, b'0')
  return socket


def send_data(socket, pcm_data):
  """Send data to server.

  Args:
    socket: socket.
    pcm_data: pcm data, bytes.

  Returns:
    Recognize result from server.
  """
  socket.send(pcm_data)
  return socket.recv().decode("utf-8")
