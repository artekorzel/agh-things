#!/bin/bash
mkdir ./generated_python
slice2py --underscore --output-dir ./generated_python ./slice/Common.ice
slice2py --underscore --output-dir ./generated_python ./slice/MyBank.ice
slice2py --underscore --output-dir ./generated_python ./slice/MyCommunicator.ice