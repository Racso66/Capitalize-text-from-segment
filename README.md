# Capitalize-text-from-segment
This code takes multiple selected words and a sentence or paragraph as input. The output consists of a segment of the sentence with the words inputted earlier left unchanged but others capitalized. Each time only one unexcluded word will be capitalized and will be mid aligned. Any of the other words that don't fall within the range of the return format will not be printed. <br /><br />
Example: if "aaa" is your input word <br />
"aaa bbb ccc ddd" is your input sentence<br />
your output will be: <br />
<pre>
                 aaa BBB ccc ddd
             aaa bbb CCC ddd
         aaa bbb ccc DDD
</pre>
where aaa is left unchanged and bbb ccc ddd each gets capitalized and printed one time and are aligned to the middle.
<br />
Use the makefile to try out the program with the given test files, or come up with your own test cases.
