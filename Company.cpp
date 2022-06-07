//
// Created by galwe on 05/06/2022.
//

#include "Company.h"
namespace Ehsan {
    Company *Company::AcquireCompany(Company *other) {

        employees_by_salary->uniteTrees(*(other->employees_by_salary));
        num_of_employees += other->num_of_employees;
        this->salary_zero_count += other->salary_zero_count;
        return this;
    }


};