# JCC指令

## 转载链接

> https://blog.csdn.net/fengshh2301/article/details/53327195

## 指令表

> JCC 条件跳转指令，CC就是指条件码。

| JCC指令     | 中文含义                                           | 英文原意                                                | 检查符号位       | 典型C应用                |
| ----------- | -------------------------------------------------- | ------------------------------------------------------- | ---------------- | ------------------------ |
| JZ/JE       | 若为0则跳转；若相等则跳转                          | jump if zero;jump if equal                              | ZF=1             | if (i == j);if (i == 0); |
| JNZ/JNE     | 若不为0则跳转；若不相等则跳转                      | jump if not zero;jump if not equal                      | ZF=0             | if (i != j);if (i != 0); |
| JS          | 若为负则跳转                                       | jump if sign                                            | SF=1             | if (i < 0);              |
| JNS         | 若为正则跳转                                       | jump if not sign                                        | SF=0             | if (i > 0);              |
| JP/JPE      | 若1出现次数为偶数则跳转                            | jump if Parity (Even)                                   | PF=1             | (null)                   |
| JNP/JPO     | 若1出现次数为奇数则跳转                            | jump if not parity (odd)                                | PF=0             | (null)                   |
| JO          | 若溢出则跳转                                       | jump if overflow                                        | OF=1             | (null)                   |
| JNO         | 若无溢出则跳转                                     | jump if not overflow                                    | OF=0             | (null)                   |
| JC/JB/JNAE  | 若进位则跳转；若低于则跳转；若不高于等于则跳转     | jump if carry;jump if below;jump if not above equal     | CF=1             | if (i < j);              |
| JNC/JNB/JAE | 若无进位则跳转；若不低于则跳转；若高于等于则跳转； | jump if not carry;jump if not below;jump if above equal | CF=0             | if (i >= j);             |
| JBE/JNA     | 若低于等于则跳转；若不高于则跳转                   | jump if below equal;jump if not above                   | ZF=1或CF=1       | if (i <= j);             |
| JNBE/JA     | 若不低于等于则跳转；若高于则跳转                   | jump if not below equal;jump if above                   | ZF=0或CF=0       | if (i > j);              |
| JL/JNGE     | 若小于则跳转；若不大于等于则跳转                   | jump if less;jump if not greater equal                  | SF != OF         | if (si < sj);            |
| JNL/JGE     | 若不小于则跳转；若大于等于则跳转；                 | jump if not less;jump if greater equal                  | SF = OF          | if (si >= sj);           |
| JLE/JNG     | 若小于等于则跳转；若不大于则跳转                   | jump if less equal;jump if not greater                  | ZF != OF 或 ZF=1 | if (si <= sj);           |
| JNLE/JG     | 若不小于等于则跳转；若大于则跳转                   | jump if not less equal;jump if greater                  | SF=0F 且 ZF=0    | if(si>sj)                |