/*An employee can apply for a loan at the beginning of every six months, but he/she will be 
sanctioned the amount according to the following company rules: 

- Rule 1 : An employee cannot enjoy more than two loans at any point of time.
- Rule 2 : Maximum permissible total loan is limited to Rs.50,000
- Rule 3 : If there is any previous dues pending that amount would be deducted and 
the balance only will be given as loan.

Write a program to read the values of the previous two loans got and process the new loan 
application and sanction the loan according to the eligibility.*/


#include <stdio.h>

int main() {
    int loan1, loan2;
    int requestedLoan;
    int totalLoan, eligibleAmount;

    printf("Enter previous loan 1 amount (0 if none): ");
    scanf("%d", &loan1);

    printf("Enter previous loan 2 amount (0 if none): ");
    scanf("%d", &loan2);

    printf("Enter requested new loan amount: ");
    scanf("%d", &requestedLoan);

    // Rule 1: Cannot have more than two loans
    if (loan1 > 0 && loan2 > 0) {
        printf("Loan Rejected: Already having two active loans.\n");
        return 0;
    }

    // Calculate total existing loan
    totalLoan = loan1 + loan2;

    // Rule 2: Maximum total loan is 50,000
    eligibleAmount = 50000 - totalLoan;

    if (eligibleAmount <= 0) {
        printf("Loan Rejected: Loan limit exceeded.\n");
        return 0;
    }

    // Rule 3: Deduct previous dues
    if (requestedLoan > eligibleAmount) {
        requestedLoan = eligibleAmount;
    }

    printf("Loan Sanctioned Amount: Rs.%d\n", requestedLoan);

    return 0;
}
