add_executable(kaleielak
  kaleielak.cc
  video-encoder.cc

  mandelbrot.cc
  julia.cc

  scene-factory.cc
  scenes/circles1.cc
  scenes/golden-spiral.cc
  scenes/golden-flower.cc
  scenes/mandel1.cc
  scenes/julia1.cc

  main.cc)

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
  -fopenmp)
