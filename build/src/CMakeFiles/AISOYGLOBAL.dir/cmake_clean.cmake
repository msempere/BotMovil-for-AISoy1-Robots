FILE(REMOVE_RECURSE
  "libAISOYGLOBAL.pdb"
  "libAISOYGLOBAL.a"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/AISOYGLOBAL.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
