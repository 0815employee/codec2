@echo off
rem Generate fading files used for channel simulation

set output_path=%1
echo Generating fading files ......

cd ../octave
octave-cli.exe --no-gui -q --eval "pkg load signal; ch_fading('%output_path%/fast_fading_samples.float', 8000, 1.0, 8000*60)"
if not %errorlevel%==0 (
    echo octave failed to run correctly .... exiting
    exit /b 1
)

octave-cli.exe --no-gui -q --eval "pkg load signal; ch_fading('%output_path%/faster_fading_samples.float', 8000, 2.0, 8000*60)"
if not %errorlevel%==0 (
    echo octave failed to run correctly .... exiting
    exit /b 1
)

exit /b 0
