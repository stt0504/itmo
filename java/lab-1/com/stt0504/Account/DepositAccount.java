package com.stt0504.Account;

import com.stt0504.User.User;

import java.time.LocalDate;

/**
 * The DepositAccount class is a type of account to which money is deposited for a fixed period of time.
 */
public class DepositAccount extends InterestBearingAccount {

    /**
     * Constructor for DepositAccount class.
     * @param ID The unique identifier of the account.
     * @param startDate The start date of the account.
     * @param endDate The end date of the account.
     * @param percent The annual percentage rate (APR) for calculating interest.
     * @param owner The owner of the account.
     * @param balance The start balance of the account.
     */
    public DepositAccount(int ID, LocalDate startDate, LocalDate endDate, double percent, User owner, double balance) {
        super(ID, startDate, endDate, percent, owner, balance);
    }

    /**
     * Withdraws the specified amount from the account's balance.
     * @param amount The amount to withdraw from the balance.
     */
    public void Withdraw(double amount) {
        if (!LocalDate.now().isAfter(endDate)) {
            throw new IllegalArgumentException("Can not withdraw before the end date");
        }
    }
}
