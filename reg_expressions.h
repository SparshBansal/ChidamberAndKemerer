#ifndef __REG_EXPRESSIONS_H_INCLUDED__
#define __REG_EXPRESSIONS_H_INCLUDED__

#include <string>

const std::string IDENTIFIER_DEF = "([A-Za-z_][A-Za-z0-9-_]*)";
const std::string TYPE_DEF = "(void\\*?|int\\*?|float\\*|double\\*?|long\\*?" + IDENTIFIER_DEF + "\\*?)"; 

const std::string CLASS_DEF = "^class +" + IDENTIFIER_DEF + "( *:: *(public|private|protected) +" + IDENTIFIER_DEF + "( *, *(private|public|protected) +" + IDENTIFIER_DEF + ")*)?$";
const std::string FUNCTION_DEF = "^" + TYPE_DEF + " +" + IDENTIFIER_DEF + " *\\(" + "( *" + TYPE_DEF + " +" + IDENTIFIER_DEF + "( *, *" + TYPE_DEF + " +" + IDENTIFIER_DEF + ")*)?\\)$";

#endif