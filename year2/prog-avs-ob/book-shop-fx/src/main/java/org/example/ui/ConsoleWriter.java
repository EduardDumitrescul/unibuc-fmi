package org.example.ui;

abstract class ConsoleWriter {
    protected static void writeLine(String msg) {
        System.out.println(msg);
    }
    protected static void write(String msg) {
        System.out.print(msg);
    }
}
