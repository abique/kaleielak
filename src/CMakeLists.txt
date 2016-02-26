add_executable(kaleielak
arc.hh
circle.hh
color.hh
fft.hh
julia.cc
julia.hh
kaleielak.cc
kaleielak.hh
main.cc
mandelbrot.cc
mandelbrot.hh
node.hh
palette.hh
pixel.hh
rectangle.hh
repeat.hh
rosace.hh
rotation.hh
scene-factory.cc
scene-factory.hh
scene.hh
scenes/circles1.cc
scenes/circles1.hh
scenes/endless-knot.cc
scenes/endless-knot.hh
scenes/golden-flower.cc
scenes/golden-flower.hh
scenes/golden-spiral.cc
scenes/golden-spiral.hh
scenes/julia1.cc
scenes/julia1.hh
scenes/mandel1.cc
scenes/mandel1.hh
transform.hh
value.hh
video-encoder.cc
video-encoder.hh
xcb-output.cc
xcb-output.hh
)

target_link_libraries(kaleielak

  # FFMPEG Debug style
  #/home/abique/develop/ffmpeg/build/libavformat/libavformat.a
  #/home/abique/develop/ffmpeg/build/libavdevice/libavdevice.a
  #/home/abique/develop/ffmpeg/build/libavfilter/libavfilter.a
  #/home/abique/develop/ffmpeg/build/libavcodec/libavcodec.a
  #/home/abique/develop/ffmpeg/build/libswresample/libswresample.a
  #/home/abique/develop/ffmpeg/build/libavutil/libavutil.a
  #va

  swscale
  avcodec
  avutil

  sndfile

  cairo
  mimosa
  -fopenmp
  xcb
  mimosa
)
