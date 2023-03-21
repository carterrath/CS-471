topc :- write('give me the cs class: '),read(C),classinfo(C,instructor(I),days(D),times(T)),write(I),nl,write(D),nl,write(T),nl.
topd :- write('give me the days you want: '),read(D),classinfo(C,instructor(I),days(D),times(T)),write(C),nl,write(I),nl,write(T),nl.

classinfo(cis444,instructor('Jing Hou'),days('M/W'),times('2:30-3:45')).
classinfo(se451,instructor('Yongjie Zheng'),days('T/TR'),times('1:00-2:15')).
classinfo(cs471,instructor('Rika Yoshii'),days('T/TR'),times('2:30-3:45')).
