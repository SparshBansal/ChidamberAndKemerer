#ifndef __REG_EXPRESSIONS_H_INCLUDED__
#define __REG_EXPRESSIONS_H_INCLUDED__

#include <string>

const std::string CLASS_DEF = "^class +([a-zA-Z0-9_-]+)( *:: *(public|private|protected) +([a-zA-Z0-9_-]+)( *, *(private|public|protected) +([a-zA-Z0-9_-]+))*)?$";

#endif