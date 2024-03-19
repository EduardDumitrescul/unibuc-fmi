package org.example.ui;

import static org.example.ui.ConsoleWriter.writeLine;

class ScreenTitle {
    private static final String bar = "################################################################";
    private ScreenTitle() {}
    static void showTitle(String title) {
        title = title.toUpperCase();
        title = "    " + title + "    ";
        int middle = bar.length() / 2;
        int len = title.length();
        writeLine(bar);
        writeLine(bar.substring(0, middle - ((len+1) / 2)) + title + bar.substring(middle + (len / 2)));
        writeLine(bar);
    }
}
