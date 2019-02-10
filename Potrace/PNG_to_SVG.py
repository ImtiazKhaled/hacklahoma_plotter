import subprocess
from PIL import Image
import numpy as np
import os

filename, file_extension = os.path.splitext('C://Potrace/alpha.png')

file_in = "alpha.png"
img = Image.open(file_in)
file_out = "alpha.bmp"
img.save(file_out)

subprocess.call('potrace -s -o alpha.svg alpha.bmp', shell=True)
