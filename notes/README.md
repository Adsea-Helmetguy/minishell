# Minishell

## Characteristics

### C1: The default value from variable expansion is an empty string
- Empty string tokens are not removed as empty strings could be valid arguments to a program

### C2: The input string is splitted by pipes into pipelines, and all programs in the pipes will run simultaneously

### C3: The shell is inspired heavily by bash, but does not provide all the functionalities of bash
- Compared to zsh, there will only be one stdin to a program in a pipeline, with the latest one being that stdin
- Compared to zsh, there will only be one stdout to a program in a pipeline, with the latest one being that stdout
- Syntax error will be thrown, and nothing gets executed in all pipelines, when it does not follow the style: <operator> <arg>, while bash may handle it
- Only a generic "Syntax Error" message will be shown and nothing specific about it is known