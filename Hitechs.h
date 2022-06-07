//
// Created by galwe on 06/06/2022.
//

#ifndef WET2_NEW_HITECHS_H
#define WET2_NEW_HITECHS_H
#define BALANCE_FACTOR 2
#define ARRAY_SIZE 16
#include "UnionFind.h"
#include "Employee.h"
#include "Company.h"
namespace Ehsan {
    typedef enum {
        SUCCESS = 0,
        FAILURE = -1,
        ALLOCATION_ERROR = -2,
        INVALID_INPUT = -3
    } StatusType;
    class Hitechs {
        int num_of_companies;
        int num_of_employees;
        UnionFind<Company> *companies;
        RankTree<int, int> *employees_by_salary;
        int salary_zero_count;
        DynamicArray<Employee> *employees;
        int salary_zero_sum;

        Hitechs(int num_of_companies):
        num_of_companies(num_of_companies),
        num_of_employees(0),
        companies(new UnionFind<Company>(num_of_companies)),
        employees_by_salary(new RankTree<int, int>()),
         salary_zero_count(0),
         employees(new DynamicArray<Employee>(ARRAY_SIZE,BALANCE_FACTOR)),
        salary_zero_sum(0)
        {
            for(int i=1;i<=num_of_companies;i++)
            {
                companies->data[i]->value=i;
            }
        }
        void AddEmployeeHelper(int employeeID, Company* company, int company_id,int grade);

        Company* FindCompany(int company_id);

        StatusType AddEmployee( int employeeID, int companyID, int grade);
        void RemovePlayerFromHitechsHelper(int PlayerID,int score,int level);
        void RemovePlayerFromCompanyHelper(Employee* employee,Company* company,int salary,int grade);
        StatusType RemoveEmployee( int employeeID);

        StatusType AcquireCompany( int companyID1, int companyID2, double factor);

        StatusType EmployeeSalaryIncrease( int employeeID, int salaryIncrease);

        StatusType PromoteEmployee( int employeeID, int bumpGrade);

        StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void * sumBumpGrade);

        StatusType AverageBumpGradeBetweenSalaryByGroup( int companyID, int lowerSalary, int higherSalary, void * averageBumpGrade);

        StatusType CompanyValue(int companyID, void * standing);


        void AddEmployeeToNewSalaryInHitechs(Employee *employee);

        void AddEmployeeToNewSalaryInCompany(Employee *employee, Company *company);

        void RemoveEmployeeFromOldSalaryInHitechs(Employee *employee);

        void RemoveEmployeeFromOldSalaryInCompany(Employee* employee, Company* company);
    };
}

#endif //WET2_NEW_HITECHS_H
