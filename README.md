# primaryMath
 自动生成四则运算算式

*  this is a console application project
*  使用如下格式启动
   *  primaryMath.exe   [parameter] [参数]
* parameter支持4个模式
  * -r 限制数值范围，该参数必须给出
  * -n 指定题目数量，程序默认生成100道
  * -a 指定答案文件
  * -e 指定练习题回答文件
    * 注意：-a -e模式需一并输入才能正确启动判题功能
    * 可以使用程序目录下提供的批处理文件运行程序

* parameter参数说明
  * -r ，-n 带一个正整数参数。如 -r 100 -n 100
  * -a ，-e 带一个文件名参数。如 -e Exercises.txt -a Answers.txt

* 功能说明：
  * 生成题目：算式有2-4个操作数，未设立查重机制，可能会出现一些重复的题目。题目生成会输出文件Exercises.txt和Answers.txt，分别是题目和答案，可以直接用文本编辑器打开Exercises文件答题。
  * 判题：判题采用的是字符串比较的方式实现的，答题必须按约分到最简，以及使用带分数形式输入，如1`3/7，任何多余的误输入都有可能导致不能正常判题，尤其是换行字符会改变后续题目的题号顺序。
  * 启动判题功能后会打印出题目答案的比较与统计情况，统计情况会输出到程序目录下的Grade.txt文件中。