import argparse
import os


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument("-trace", required=True)
    parser.add_argument("-out", default="./")
    args = parser.parse_args()

    with open(args.trace) as f:
        content = f.read().split("\n")

    output = ""
    for item in content:
        test_items = item.split(", ")
        sentence = {}
        for test_item in test_items:
            temp = test_item.split(": ")
            if temp[0] == "Load":
                sentence[temp[0]] = "true" if temp[1] == "0" else "false"
            else:
                sentence[temp[0]] = temp[1]
        output += "test_args[{Node}].test_cases.emplace_back({Cycle}, test_case_t{{{Load}, {Address}, {Cycle}}});\n".format(
            **sentence)
    with open(os.path.join(args.out, "test.log"), "w") as f:
        f.write(output)


if __name__ == '__main__':
    main()
