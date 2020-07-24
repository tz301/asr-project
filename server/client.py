#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/23
"""客户端样例."""
import logging
import wave
from pathlib import Path

import zmq


def __get_pcm_data_list(wav_file):
  """Get pcm data list, which is split by 200ms.

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
  return [data[i:i + chunk] for i in range(0, len(data), chunk)]


def __init_socket(host):
  """Init socket.

  Args:
    host: host.

  Returns:
    socket.
  """
  context = zmq.Context()
  socket = context.socket(zmq.REQ)  # pylint: disable=no-member
  socket.connect(host)
  __send_data(socket, b'0')
  return socket


def __send_data(socket, pcm_data):
  """Send data to server.

  Args:
    socket: socket.
    pcm_data: pcm data, bytes.

  Returns:
    Recognize result from server.
  """
  socket.send(pcm_data)
  return socket.recv().decode("utf-8")


def __main():
  """Main function."""
  wav_file = Path(__file__).absolute().parent.parent / 'tests/test.wav'
  pcm_data_list = __get_pcm_data_list(wav_file)
  socket = __init_socket('tcp://localhost:6557')

  total = len(pcm_data_list)
  for i, pcm_data in enumerate(pcm_data_list):
    if i == total - 1:
      pcm_data += b'0'  # Add one data for end flag.
    transcript = __send_data(socket, pcm_data)
    logging.info(transcript)


if __name__ == "__main__":
  logging.basicConfig(format="%(asctime)s %(name)s %(levelname)s %(message)s",
                      level=logging.INFO)
  __main()
