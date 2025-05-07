import re
import os

def split_file(input_filename):
    """
    Splits a large text file into smaller files based on the pattern
    "/* including file '<filepath>' */", handling potential
    additional lines and varying whitespace.

    Args:
        input_filename (str): The path to the input text file.
    """
    try:
        with open(input_filename, 'r') as infile:
            content = infile.read()
    except FileNotFoundError:
        print(f"Error: Input file '{input_filename}' not found.")
        return

    pattern = r"\/\* including file\s+'(.+?)'\s+\*\/(?:.*\n)?"
    matches = re.finditer(pattern, content)
    inclusion_directives = [(match.group(1), match.end()) for match in matches]

    if not inclusion_directives:
        print("No 'including file' directives found in the input file.")
        return

    # Create output directories if they don't exist
    for file_path, _ in inclusion_directives:
        output_dir = os.path.dirname(file_path)
        if output_dir and not os.path.exists(output_dir):
            os.makedirs(output_dir)

    start_index = 0
    for i, (file_path, end_directive_index) in enumerate(inclusion_directives):
        # The content for the current file starts after the current directive
        start_content_index = end_directive_index
        # The content for the current file ends before the start of the next directive
        end_content_index = len(content)
        if i + 1 < len(inclusion_directives):
            end_content_index = inclusion_directives[i + 1][1]

        file_content = content[start_content_index:end_content_index].strip()

        try:
            with open(file_path, 'w') as outfile:
                outfile.write(file_content)
            print(f"Created file: '{file_path}'")
        except Exception as e:
            print(f"Error writing to file '{file_path}': {e}")

if __name__ == "__main__":
    input_file = input("Enter the name of the input file: ")
    split_file(input_file)
    print("File splitting process completed.")