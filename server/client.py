#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/23
"""Client example."""
import logging

# pylint: disable=import-error
from utils import ASR_IP, get_pcm_data_list, init_socket, send_data, TEST_WAV


def __main():
  """Main function."""
  socket = init_socket(ASR_IP)
  for pcm_data in get_pcm_data_list(TEST_WAV):
    transcript = send_data(socket, pcm_data)
    logging.info(transcript)


if __name__ == "__main__":
  logging.basicConfig(format="%(asctime)s %(name)s %(levelname)s %(message)s",
                      level=logging.INFO)
  __main()
