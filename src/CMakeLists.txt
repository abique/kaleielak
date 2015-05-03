add_executable(kaleielak
  kaleielak.cc
  video-encoder.cc
  main.cc)

target_link_libraries(kaleielak
  cairo
  vpx
  mimosa)