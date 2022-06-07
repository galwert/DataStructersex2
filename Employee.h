//
// Created by galwe on 06/06/2022.
//

#ifndef WET2_NEW_EMPLOYEE_H
#define WET2_NEW_EMPLOYEE_H


namespace Ehsan
{

    class Employee
    {
    public:
        int original_company;
        int employee_id;
        int salary;
        int grade;

        Employee(int original_company = 0 ,int id = 0 , int salary = 0 , int grade=  0 ):
                original_company(original_company),
                employee_id(id),
                salary(salary),
                grade(grade)
        {}
        Employee(Employee * employee):
                original_company(employee->original_company),
                employee_id(employee->employee_id),
                salary(employee->salary),
                grade(employee->grade)
        {

        }
        ~Employee() = default;
        Employee& operator=(const Employee& employee) = default;

    };




} // namespace Ehsan




#endif //WET2_NEW_EMPLOYEE_H
