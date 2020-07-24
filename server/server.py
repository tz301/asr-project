#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Created by tz301 on 2020/07/03
"""Deploy."""
import os
from pathlib import Path
from flask import Flask, request, url_for, send_from_directory, render_template
from werkzeug.utils import secure_filename
import logging

app = Flask(__name__)

__ALLOWED_EXTENSIONS = {'wav'}


# html = '''
#   <!DOCTYPE html>
#   <title>Upload File</title>
#   <h1>Upload Wav</h1>
#   <form method=post enctype=multipart/form-data>
#     <input type=file name=file>
#     <input type=submit value=上传>
#   </form>
# '''
#
#
# def allowed_file(filename):
#   return Path(filename).suffix in __ALLOWED_EXTENSIONS
#
#
# @app.route('/uploads/<filename>')
# def uploaded_file(filename):
#   return send_from_directory(app.config['UPLOAD_FOLDER'], filename)
#
#
# @app.route('/', methods=['GET', 'POST'])
# def upload_file():
#   if request.method == 'POST':
#     file = request.files['file']
#     if file and allowed_file(file.filename):
#       filename = secure_filename(file.filename)
#       file.save(app.config['UPLOAD_FOLDER'] / filename)
#       file_url = url_for('uploaded_file', filename=filename)
#       return html + '<br><img src=' + file_url + '>'
#   return html

global INDEX
INDEX = 0

def online_asr():
  global INDEX

  chunks = ["甚至出现", "交易几乎", "停滞的情况"]
  ret = "".join(chunks[:INDEX + 1])
  if INDEX == len(chunks) - 1:
    INDEX = 0
    stop = 1
  else:
    INDEX += 1
    stop = 0
  return ret, stop


@app.route('/aishell',methods=['GET','POST'])
def aishell():
  ret, stop = online_asr()
  return render_template("index.html",s = ret,stop=stop)


@app.route('/',methods=['GET','POST'])
def home():
  return render_template("index.html",s = " ",stop=1)


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

