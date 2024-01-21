#ifndef SRC_CONTROLLER_CREDITCONTROLLER_H
#define SRC_CONTROLLER_CREDITCONTROLLER_H

#include "../Model/creditmodel.h"

namespace s21 {
class CreditController {
 public:
  CreditController(){};
  ~CreditController(){};

  // Calculate result
  CreditResult& Run(CreditInfo& info) { return model_.CalculateResult(info); }

 private:
  CreditModel model_{};
};
}  // namespace s21
#endif  // SRC_CONTROLLER_CREDITCONTROLLER_H
