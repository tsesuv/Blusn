# if.chs tsesuv notsel 2025/10/11
# OUTはCのprintfと同じ感じになるかな？
[DEF::MAIN::(
	(LET::X::0)
	(IN::X) # 逐次処理はそのままつなげるだけ
	(IF::(GT::X::3)::(
		OUT::'$0 is Greater!%j"'::X
	)::(
		OUT::'$0 is Smaller!%j"'::X
	))
)]
