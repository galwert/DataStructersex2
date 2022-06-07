//
// Created by galwe on 05/06/2022.
//

#ifndef WET2_NEW_COMPANY_H
#define WET2_NEW_COMPANY_H

#include "RankTree.h"
#include "DynamicArray.h"
#define BALANCE_FACTOR 2
#define ARRAY_SIZE 16
namespace Ehsan
{
    class Company
    {
    public:
        int num_of_employees;
        RankTree<int,int> *employees_by_salary;
        int salary_zero_count;
        int value;
        int salary_zero_sum;
        explicit Company(int value):
                num_of_employees(0),//initializes number of players
                employees_by_salary(new RankTree<int,int>()),
                salary_zero_count(0),
                value(0),
                salary_zero_sum(0)
        {

        }
        ~Company()
        {
            delete employees_by_salary;
        }


        Company *AcquireCompany(Company *other);
    };

} // namespace Ehsan

#endif //WET2_NEW_COMPANY_H
