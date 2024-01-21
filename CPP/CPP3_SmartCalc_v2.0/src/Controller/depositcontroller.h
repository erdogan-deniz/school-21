#ifndef SRC_CONTROLLER_DEPOSITCONTROLLER_H
#define SRC_CONTROLLER_DEPOSITCONTROLLER_H

#include "../Model/depositmodel.h"

namespace s21 {
class DepositController {
 public:
  DepositController(){};
  ~DepositController(){};

  // Calculate result
  DepositResult& Run(DepositInfo& deposit_info) {
    return model_.Calculate(deposit_info);
  }

 private:
  DepositModel model_{};
};
}  // namespace s21
#endif  // SRC_CONTROLLER_DEPOSITCONTROLLER_H