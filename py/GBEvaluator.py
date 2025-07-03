import math
from GBLinkedListStack import GBLinkedListStack

class GBEvaluator:
    def __init__(self):
        self.ops = GBLinkedListStack()   # 연산자 스택
        self.vals = GBLinkedListStack()  # 피연산자 스택

    def evaluate(self, expression: str) -> float:
        tokens = expression.strip().split()

        for token in tokens:
            if token == "(":
                continue
            elif token in {"+", "-", "*", "/", "sqrt"}:
                self.ops.push(token)
            elif token == ")":
                op = self.ops.pop()
                v = self.vals.pop()

                if op == "+":
                    v = self.vals.pop() + v
                elif op == "-":
                    v = self.vals.pop() - v
                elif op == "*":
                    v = self.vals.pop() * v
                elif op == "/":
                    v = self.vals.pop() / v
                elif op == "sqrt":
                    v = math.sqrt(v)

                self.vals.push(v)
            else:
                # 숫자일 경우
                self.vals.push(float(token))

        return self.vals.pop()
    
if __name__ == "__main__":
    evaluator = GBEvaluator()

    expr = "( 1 + ( ( 2 + 3 ) * ( 4 * 5 ) ) )"
    result = evaluator.evaluate(expr)

    print("결과:", result)  # 출력: 결과: 101.0