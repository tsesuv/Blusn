from enum import Enum, auto

class tkType(Enum):
	TK_OP = auto()
	TK_NEWL = auto()
	TK_NUM = auto()
	TK_STR = auto()
	TK_IDEN = auto()
	TK_KEYW = auto()
	TK_LPAREN = auto()
	TK_RPAREN = auto()
	TK_LBRACKET = auto()
	TK_RBRACKET = auto()
	TK_COMMA = auto()
	TK_COLON = auto()
	TK_DOT = auto()
	TK_AT = auto()
	TK_VOID = auto()
	TK_EOF = auto()

class Token:
	def __init__(self, type, value):
		self.type = type
		self.value = value

	def __repr__(self):
		return f"Token({self.type}, {self.value})"

def tokenalizer(code):
	tokens = []
	for char in code:
		if char.isdigit():
			tokens.append(Token(tkType.TK_NUM, int(char)))
		elif char == '@':
			tokens.append(Token(tkType.TK_AT, char))

	return tokens
