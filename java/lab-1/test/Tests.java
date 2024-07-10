import com.stt0504.Account.Account;
import com.stt0504.Bank.Bank;
import com.stt0504.Transaction.Refill;
import com.stt0504.Transaction.Transaction;
import com.stt0504.Transaction.Transfer;
import com.stt0504.Transaction.Withdraw;
import com.stt0504.User.User;

import java.time.LocalDate;
import java.util.NavigableMap;
import java.util.TreeMap;

import static com.stt0504.Account.AccountType.*;
import static com.stt0504.Transaction.TransactionStatus.*;
import static org.junit.jupiter.api.Assertions.assertEquals;


public class Tests {

    Bank bank1;
    User notSuspiciousClient;
    User suspiciousClient;

    Account debitAccount1;
    Account depositAccount1;
    Account creditAccount1;

    Account debitAccount2;
    Account depositAccount2;
    Account creditAccount2;

    public Tests() {
        NavigableMap<Double, Double> percents = new TreeMap<>();
        percents.put(1000.0, 2.0);
        percents.put(5000.0, 3.0);
        percents.put(10000.0, 3.65);

        bank1 = new Bank("TestBank", 10.0, percents, 3.65, 10000.0, 10000.0, 8000.0);

        notSuspiciousClient = new User.Builder()
                .setName("Name1")
                .setSurname("Surname1")
                .setAddress("Address1")
                .setPassportNumber("Passport1")
                .setLogin("login1")
                .setPassword("password1")
                .build();

        suspiciousClient = new User.Builder()
                .setName("Name2")
                .setSurname("Surname2")
                .setLogin("login2")
                .setPassword("password2")
                .build();


        bank1.AddUser(notSuspiciousClient);

        LocalDate endDate = LocalDate.now().plusYears(1);
        bank1.CreateAccount(notSuspiciousClient, DEBIT, LocalDate.of(2024, 3, 31), endDate, 0);
        bank1.CreateAccount(notSuspiciousClient, DEPOSIT, LocalDate.of(2024, 3, 31), endDate, 10000);
        bank1.CreateAccount(notSuspiciousClient, CREDIT, LocalDate.of(2024, 3, 31), endDate, 0);

        bank1.CreateAccount(suspiciousClient, DEBIT, LocalDate.of(2024, 3, 31), endDate, 0);
        bank1.CreateAccount(suspiciousClient, DEPOSIT, LocalDate.of(2024, 3, 31), endDate, 10000);
        bank1.CreateAccount(suspiciousClient, CREDIT, LocalDate.of(2024, 3, 31), endDate, 0);

        debitAccount1 = bank1.GetAccount(notSuspiciousClient, 1);
        depositAccount1 = bank1.GetAccount(notSuspiciousClient, 2);
        creditAccount1 = bank1.GetAccount(notSuspiciousClient, 3);

        debitAccount2 = bank1.GetAccount(suspiciousClient, 4);
        depositAccount2 = bank1.GetAccount(suspiciousClient, 5);
        creditAccount2 = bank1.GetAccount(suspiciousClient, 6);
    }

    @org.junit.jupiter.api.Test
    public void RefillTest_Success() {
        Transaction refill = new Refill(bank1, 1000, debitAccount1);
        refill.Execute();
        assertEquals(1000, debitAccount1.getBalance());
    }

    @org.junit.jupiter.api.Test
    public void WithdrawTest_NotEnoughMoney() {
        Transaction withdraw = new Withdraw(bank1, 200, debitAccount1);
        withdraw.Execute();
        assertEquals(FAILED, withdraw.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void WithdrawTest_SuspiciousClient_WithdrawLimit() {
        Transaction withdraw = new Withdraw(bank1, 10001, debitAccount2);
        withdraw.Execute();
        assertEquals(FAILED, withdraw.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void WithdrawTest_Deposit_Failed() {
        Transaction withdraw = new Withdraw(bank1, 1000, depositAccount1);
        withdraw.Execute();
        assertEquals(FAILED, withdraw.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void WithdrawTest_Success() {
        new Refill(bank1, 1000, bank1.GetAccount(notSuspiciousClient, 1)).Execute();
        Transaction withdraw = new Withdraw(bank1, 200, bank1.GetAccount(notSuspiciousClient, 1));
        withdraw.Execute();
        assertEquals(COMPLETED, withdraw.getStatus());
        assertEquals(800, bank1.GetAccount(notSuspiciousClient, 1).getBalance());
    }

    @org.junit.jupiter.api.Test
    public void WithdrawTest_Cancel() {
        new Refill(bank1, 1000, debitAccount1).Execute();

        Transaction withdraw = new Withdraw(bank1, 200, debitAccount1);
        withdraw.Execute();
        assertEquals(COMPLETED, withdraw.getStatus());

        assertEquals(800, debitAccount1.getBalance());
        withdraw.Cancel();
        assertEquals(CANCELLED, withdraw.getStatus());
        assertEquals(1000, debitAccount1.getBalance());
    }

    @org.junit.jupiter.api.Test
    public void CreditLimitTest() {
        Transaction withdraw1 = new Withdraw(bank1, 9980, creditAccount1);
        withdraw1.Execute();
        assertEquals(COMPLETED, withdraw1.getStatus());
        Transaction withdraw2 = new Withdraw(bank1, 1, creditAccount1);
        withdraw2.Execute();
        assertEquals(FAILED, withdraw2.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void TransferTest_NotEnoughMoney() {
        new Refill(bank1, 1000, debitAccount1).Execute();

        Transaction transfer2 = new Transfer(bank1, 1001, debitAccount1, creditAccount1);
        transfer2.Execute();
        assertEquals(FAILED, transfer2.getStatus());

        Transaction transfer1 = new Transfer(bank1, 1000, debitAccount1, creditAccount1);
        transfer1.Execute();
        assertEquals(COMPLETED, transfer1.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void TransferTest_SuspiciousClient_TransferLimit() {
        new Refill(bank1, 20000, debitAccount2).Execute();
        Transaction transfer1 = new Transfer(bank1, 8000, debitAccount2, debitAccount1);
        transfer1.Execute();
        assertEquals(COMPLETED, transfer1.getStatus());

        Transaction transfer2 = new Transfer(bank1, 8001, debitAccount2, debitAccount1);
        transfer2.Execute();
        assertEquals(FAILED, transfer2.getStatus());
    }

    @org.junit.jupiter.api.Test
    public void TransferSuccessTest() {
        new Refill(bank1, 1000, debitAccount1).Execute();
        Transaction transfer = new Transfer(bank1, 200, debitAccount1, creditAccount1);
        transfer.Execute();
        assertEquals(COMPLETED, transfer.getStatus());
        assertEquals(800, debitAccount1.getBalance());
        assertEquals(200, creditAccount1.getBalance());
    }

    @org.junit.jupiter.api.Test
    public void TransferTest_Cancel() {
        new Refill(bank1, 1000, debitAccount1).Execute();

        Transaction transfer = new Transfer(bank1, 200, debitAccount1, creditAccount1);
        transfer.Execute();
        assertEquals(COMPLETED, transfer.getStatus());
        assertEquals(800, debitAccount1.getBalance());
        assertEquals(200, creditAccount1.getBalance());

        transfer.Cancel();
        assertEquals(CANCELLED, transfer.getStatus());
        assertEquals(1000, debitAccount1.getBalance());
        assertEquals(0, creditAccount1.getBalance());
    }

    @org.junit.jupiter.api.Test
    public void BalanceAtDateDebitTest() {
        Account account = bank1.GetAccount(notSuspiciousClient, 1);
        new Refill(bank1, 100000, account).Execute();
        assertEquals(100300, account.CountBalanceAtDate(LocalDate.of(2024, 4, 30)));
    }

    @org.junit.jupiter.api.Test
    public void BalanceAtDateDepositTest() {
        Account account = bank1.GetAccount(notSuspiciousClient, 2);
        assertEquals(10030, account.CountBalanceAtDate(LocalDate.of(2024, 4, 30)));
    }

    @org.junit.jupiter.api.Test
    public void CreditCommissionTest() {
        Account account = bank1.GetAccount(notSuspiciousClient, 3);
        Transaction withdraw = new Withdraw(bank1, 200, bank1.GetAccount(notSuspiciousClient, 3));
        withdraw.Execute();
        Transaction withdraw2 = new Withdraw(bank1, 7000, bank1.GetAccount(notSuspiciousClient, 3));
        withdraw2.Execute();
        assertEquals(-7220.0, account.getBalance());
    }
}
