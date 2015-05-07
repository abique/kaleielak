add_executable(kaleielak
  kaleielak.cc
  video-encoder.cc

  scene-factory.cc
  scenes/circles1.cc

  main.cc)

target_link_libraries(kaleielak
  cairo
  avcodec
  vpx
  mimosa)