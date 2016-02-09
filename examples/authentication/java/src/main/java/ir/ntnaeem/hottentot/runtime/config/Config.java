package ir.ntnaeem.hottentot.runtime.config;


import ir.ntnaeem.hottentot.runtime.exception.MainArgsNotCorrectException;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;

public class Config {
  public static String configPath = "";
  public static boolean isVerboseMode = false;
  public static final String USAGE_HELP_STRING = "usage : -v --config-path /path/to/config/file ";
  public static int threadPoolSize = 5;
  public static boolean isGCEnabledMode = false;

  public static void setConfigPropertiesFromConfigFile() throws IOException {
    if (!configPath.equals("")) {
      BufferedReader reader = new BufferedReader(new FileReader(configPath));
      String line;
      while ((line = reader.readLine()) != null) {
        String[] splitedLine = line.split("\\=");
        if (splitedLine[0].equals("THREAD_POOL_SIZE")) {
          threadPoolSize = Integer.parseInt(splitedLine[1]);
        }
      }
    }
  }

  public static void setMainArgs(String[] args) {
    int mainArgsCounter = 0;
    while (mainArgsCounter < args.length) {
      if (args[mainArgsCounter].equals("--config-path")) {
        configPath = args[mainArgsCounter + 1];
        mainArgsCounter += 2;
      } else if (args[mainArgsCounter].equals("-v")) {
        isVerboseMode = true;
        mainArgsCounter++;
      } else if (args[mainArgsCounter].equals("-gc")) {
        isGCEnabledMode = true;
        mainArgsCounter++;
      } else {
        mainArgsCounter++;
      }
    }
  }

}
