package com.stt0504.Account;

import com.stt0504.User.User;

import java.time.LocalDate;

/**
 * The InterestBearingAccount class is a type of account that bears the interest.
 */

public abstract class InterestBearingAccount extends Account {

    /** The bearing percent. */
    protected double percent;

    /** The amount of accrued interest. */
    protected double monthSum;

    /**
     * Constructor for InterestBearingAccount class.
     * @param ID The unique identifier of the account.
     * @param startDate The start date of the account.
     * @param endDate The end date of the account.
     * @param percent The annual percentage rate for calculating interest.
     * @param owner The owner of the account.
     * @param balance The start balance of the account.
     */

    public InterestBearingAccount(int ID, LocalDate startDate, LocalDate endDate, double percent, User owner, double balance) {
        super(ID, startDate, endDate, owner, balance);
        this.percent = percent;
    }

    /**
     * Calculates and returns the account balance on the specified date.
     * @param date The date for which to calculate the balance.
     * @return The balance of the account on the specified date.
     */

    public double CountBalanceAtDate(LocalDate date) {
        LocalDate date2 = date;
        if (date2.getDayOfMonth() != date2.lengthOfMonth()) {
            date2 = date2.minusMonths(1).withDayOfMonth(date2.minusMonths(1).lengthOfMonth());
        }

        double balance = this.balance;

        LocalDate date1 = this.startDate;

        for (int k = 0; k < date1.until(date2).getDays(); k++) {
            balance += this.balance * percent / 100 / 365;
        }

        return balance;
    }

    /**
     * Updates the account balance by adding the accumulated interest for the current month.
     */
    public void Update() {
        balance += monthSum;
        monthSum = 0;
    }

    /**
     * Calculates the sum of interest for current day based on the balance and percent.
     */
    public void UpdateForDay() {
        monthSum = balance * percent / 100 / 365;
    }


}
