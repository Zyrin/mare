
#include "Statement.h"
#include "Namespace.h"
#include "Engine.h"
#include "Script.h"

void BlockStatement::execute(Namespace& space)
{
  for(List<Statement*>::Node* i = statements.getFirst(); i; i = i->getNext())
    i->data->execute(space);
}

void AssignStatement::execute(Namespace& space)
{
  space.addVariable(variable, value);
}

void BinaryStatement::execute(Namespace& space)
{
  leftOperand->execute(space);
  rightOperand->execute(space);
}

void StringStatement::execute(Namespace& space)
{
  space.addVariable(value, 0);
}

void ReferenceStatement::execute(Namespace& space)
{
  Script* script = space.getEngine().resolveReference(variable);
  if(script)
    script->execute(space);
}
