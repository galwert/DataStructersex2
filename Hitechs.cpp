//
// Created by galwe on 06/06/2022.
//

#include "Hitechs.h"
namespace Ehsan {
    Company* Hitechs::FindCompany(int company_id)
    {
        Company* to_find;
        int index = companies->Find(company_id);
        if (index < 0)
        {
            return nullptr; // in case the groups doesnt exist
        }
        to_find =companies->data[index];
        return to_find;
    }
    void Hitechs::AddEmployeeHelper(int employeeID, Company* company, int company_id,int grade)
    {
        this->salary_zero_count++;
        this->num_of_employees++;
        this->salary_zero_sum+=grade;

        company->num_of_employees++;
        company->salary_zero_count++;
        company->salary_zero_sum+=grade;

        this->companies->size[this->companies->Find(company_id)]++;
    }

    Ehsan::StatusType Hitechs::AddEmployee(int employeeID, int companyID, int grade) {
        if(employeeID<=0||companyID<=0||companyID>num_of_companies||grade<=0)
        {
            return INVALID_INPUT;
        }
        // checking if the players already exists
        if(this->employees->find(employeeID)!= nullptr)
        {
            return FAILURE;
        }
        Employee* employee =new Employee(companyID,employeeID,0,grade);
        this->employees->insert(employeeID,employee);
        Company* company_to_find = FindCompany(companyID);
        AddEmployeeHelper(employeeID,company_to_find,companyID,grade);
        return SUCCESS;
    }


    void Hitechs::RemovePlayerFromCompanyHelper(Employee* employee,Company* company,int salary,int grade)
    {
        int group_index = this->companies->Find(employee->original_company);
        company->num_of_employees--;
        this->companies->size[group_index]--;
        if(salary == 0)
        {
            company->salary_zero_count--;
            company->salary_zero_sum-=grade;
        }
        else
        {
        company->employees_by_salary->find(salary)->decreaseAllNodesInTrack(grade);
            if( company->employees_by_salary->find(salary)->data== 0) {
                company->employees_by_salary->remove(salary);
            }
            }
        }

    void Hitechs::RemovePlayerFromHitechsHelper(int PlayerID,int salary,int grade)
    {
        this->num_of_employees--;
        if(salary == 0)
        {
            salary_zero_count--;
            salary_zero_sum-=grade;
        }
        else
        {
            employees_by_salary->find(salary)->decreaseAllNodesInTrack(grade);
            if( employees_by_salary->find(salary)->data== 0) {
                employees_by_salary->remove(salary);
            }

        }
        return;
    }
    Ehsan::StatusType Hitechs::RemoveEmployee(int employeeID) {
        if(employeeID <= 0)
        {
            return INVALID_INPUT;
        }
        Employee* player_to_find =this->employees->find(employeeID);
        if( player_to_find == nullptr)
        {
            return FAILURE;
        }
        Company* group_to_find = FindCompany(player_to_find->original_company);

        RemovePlayerFromHitechsHelper(employeeID,player_to_find->salary,player_to_find->grade);
        RemovePlayerFromCompanyHelper(player_to_find,group_to_find,player_to_find->salary,player_to_find->grade);

        employees->remove(employeeID);
        return SUCCESS;
    }



    StatusType Hitechs::AcquireCompany(int companyID1, int companyID2, double factor)
    {if(companyID1<=0||companyID1>num_of_companies||companyID2<=0||companyID2>num_of_companies)
        {
            return INVALID_INPUT;
        }
        this->companies->Union(companyID1,companyID2);
        /// update company value
        return SUCCESS;
    }


    void Hitechs::RemoveEmployeeFromOldSalaryInHitechs(Employee* employee)
    {
        // this->num_of_players--; // no need because we're gonna readd him in a second
        if(employee->salary == 0)
        {
            salary_zero_count--;
            salary_zero_sum-=employee->salary;
        }
        else
        {
            employees_by_salary->find(employee->salary)->decreaseAllNodesInTrack(employee->grade);
            if( employees_by_salary->find(employee->salary)->data == 0 )
            {
                employees_by_salary->remove(employee->salary);
            }

        }
    }
    void Hitechs::RemoveEmployeeFromOldSalaryInCompany(Employee* employee, Company* company)
    {
        if(employee->salary == 0)
        {
            company->salary_zero_count--;
            company->salary_zero_sum-=employee->salary;
        }
        else {

            company->employees_by_salary->find(employee->salary)->decreaseAllNodesInTrack(employee->grade);
            if (company->employees_by_salary->find(employee->salary)->data == 0) {

                company->employees_by_salary->remove(employee->salary);
            }

        }
    }
    void Hitechs::AddEmployeeToNewSalaryInCompany(Employee* employee, Company* company)
    {

        if(company->employees_by_salary->find(employee->salary) == nullptr)
        {
            company->employees_by_salary->insert(employee->salary,0);
        }
        company->employees_by_salary->find(employee->salary)->increaseAllNodesInTrack(employee->grade);
        return;
    }
    void Hitechs::AddEmployeeToNewSalaryInHitechs(Employee* employee)
    {

        if( employees_by_salary->find(employee->salary) == nullptr)
        {
            employees_by_salary->insert(employee->salary,0);
        }
        employees_by_salary->find(employee->salary)->increaseAllNodesInTrack(employee->grade);

        return;
    }

    StatusType Hitechs::EmployeeSalaryIncrease(int employeeID, int salaryIncrease) {
        if(employeeID <= 0 || salaryIncrease<=0)
        {
            return INVALID_INPUT;
        }
        Employee* employee_to_find = this->employees->find(employeeID);
        if(employee_to_find == nullptr)
        {
            return FAILURE;
        }
        Company* company_to_find = FindCompany(employee_to_find->original_company);

        RemoveEmployeeFromOldSalaryInHitechs(employee_to_find);
        RemoveEmployeeFromOldSalaryInCompany(employee_to_find,company_to_find);

        employee_to_find->salary+=salaryIncrease;//update the player's level to the new one

        AddEmployeeToNewSalaryInHitechs(employee_to_find);
        AddEmployeeToNewSalaryInCompany(employee_to_find,company_to_find);

        return SUCCESS;
    }

    StatusType Hitechs::PromoteEmployee(int employeeID, int bumpGrade) {
        if(employeeID <= 0 || bumpGrade<=0)
        {
            return INVALID_INPUT;
        }
        Employee* employee_to_find = this->employees->find(employeeID);
        if(employee_to_find == nullptr)
        {
            return FAILURE;
        }
        Company* company_to_find = FindCompany(employee_to_find->original_company);
        if(employee_to_find->salary == 0)
        {
            company_to_find->salary_zero_sum+=bumpGrade;
        }
        else
        {
            company_to_find->employees_by_salary->find(employee_to_find->salary)->increaseAllNodesInTrack(bumpGrade);
        }
        return SUCCESS;
    }

    StatusType Hitechs::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m, void *sumBumpGrade) {
        return FAILURE;
    }

    StatusType Hitechs::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary,
                                                             void *averageBumpGrade) {
        return FAILURE;
    }

    StatusType Hitechs::CompanyValue(int companyID, void *standing) {
        if(companyID<=0||companyID>num_of_companies)
        {
            return INVALID_INPUT;
        }
        standing= reinterpret_cast<void *>(this->companies->data[companyID]->value);
    }

}