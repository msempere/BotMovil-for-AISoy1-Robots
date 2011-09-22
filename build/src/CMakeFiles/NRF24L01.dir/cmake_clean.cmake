FILE(REMOVE_RECURSE
  "libNRF24L01.pdb"
  "libNRF24L01.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/NRF24L01.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
