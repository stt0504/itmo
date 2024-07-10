package com.stt0504.Transaction;

/**
 * The TransactionStatus enum represents the status of a financial transaction.
 * It defines various states that a transaction can be in.
 */
public enum TransactionStatus {
    /**
     * The transaction has been created but not yet processed.
     */
    CREATED,

    /**
     * The transaction is currently being processed.
     */
    WORKING,

    /**
     * The transaction has failed to complete successfully.
     */
    FAILED,

    /**
     * The transaction has been successfully completed.
     */
    COMPLETED,

    /**
     * The transaction has been cancelled.
     */
    CANCELLED
}
