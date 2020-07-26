#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/23
"""Client example."""
import logging
from argparse import ArgumentParser

# pylint: disable=import-error
from utils import asr_ip, get_pcm_data_list, init_socket, send_data, TEST_WAV


def __main():
  """Main function."""
  parser = ArgumentParser(description="Test asr server.")
  parser.add_argument("asr_port", type=int, help="asr server port.")
  args = parser.parse_args()

  socket = init_socket(asr_ip(args.asr_port))
  for pcm_data in get_pcm_data_list(TEST_WAV):
    transcript = send_data(socket, pcm_data)
    logging.info(transcript)


if __name__ == "__main__":
  logging.basicConfig(format="%(asctime)s %(name)s %(levelname)s %(message)s",
                      level=logging.INFO)
  __main()
