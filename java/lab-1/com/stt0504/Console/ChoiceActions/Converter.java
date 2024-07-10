package com.stt0504.Console.ChoiceActions;

/**
 * The Converter interface represents a functional interface for converting an input of type T to an output of type R.
 * @param <T> The type of input to be converted.
 * @param <R> The type of output after conversion.
 */
public interface Converter<T, R> {

    /**
     * Converts the input of type T to an output of type R.
     * @param input The input to be converted.
     * @return The converted output.
     */
    R convert(T input);
}
