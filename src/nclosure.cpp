#include "nclosure.h"

namespace napkin {

NClosure::NClosure(LambdaExpr *t_expr, const Environment *t_environment) {
  expr = t_expr;
  // Create a new environment and copy over the environment passed in the
  // contructor
  environment = new Environment;
  *environment = *t_environment;
}

/**
 * Executes the function.
 * TODO
 */
NObject *NClosure::call(Interpreter *interpreter,
                        std::vector<NObject *> arguments) {
  Environment *tempEnvironment = new Environment(this->environment);
  // Match parameters with arguments
  for (unsigned long i = 0; i < arguments.size(); i++) {
    tempEnvironment->declareVar(expr->parameters[i]->token.getLexeme(),
                                arguments[i]);
  }

  // Either get the resulting value from executing to the end of the block stmt
  // or from a return stmt that throws a ReturnException
  NObject *result = nullptr;
  try {
    result = interpreter->executeBlockStmt(expr->body, tempEnvironment);
  } catch (ReturnException returnValue) {
    result = returnValue.value;
  }

  delete tempEnvironment;
  return result;
}

int NClosure::arity() {
  return expr->parameters.size();
}

}
