FILE(REMOVE_RECURSE
  "libDRACO_GPIO_MOD.pdb"
  "libDRACO_GPIO_MOD.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/DRACO_GPIO_MOD.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
