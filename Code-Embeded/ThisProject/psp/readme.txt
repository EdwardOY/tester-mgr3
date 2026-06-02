基础程序： 完成日期2023.2.22
1 在cbx生成的代码基础上开发，
2 usart ，
   2.1 时钟使能，nvic 、gpio配置 初始化 放置在 usart.h里
   2.2 中断处理函数和  fputc->printf(不使用microLIB，禁用半主机)  移入 shell_uart.c里