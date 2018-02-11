from nltk.tokenize import sent_tokenize


def lines(a, b):
    """Return lines in both a and b"""
    linesInCommon = []

    # split a et b into list of lines
    a = a.splitlines()
    b = b.splitlines()

    # compare and return list of line in common while avoiding duplicates
    for line in a:
        if line in b and not line in linesInCommon:
            linesInCommon.append(line)
    return linesInCommon


def sentences(a, b):
    """Return sentences in both a and b"""
    sentencesInCommon = []

    # split a and b into list of sentences
    a = sent_tokenize(a, language='english')
    b = sent_tokenize(b, language='english')

    # compare and return list of sentences in common while avoiding duplicates
    for sentence in a:
        if sentence in b and not sentence in sentencesInCommon:
            sentencesInCommon.append(sentence)
    return sentencesInCommon


def substrings(a, b, n):
    """Return substrings of length n in both a and b"""

    # function to get all substrings of length n in a given string
    def getSubstring(s, n):
        substrings = []
        i = 0
        while i + n <= len(s):
            substrings.append(s[i:i + n])
            i += 1
        return substrings

    # return list of all substrings of length n in a and b using function substrings()
    a = getSubstring(a, n)
    b = getSubstring(b, n)
    substringsInCommon = []

    # compare and return list of substrings in common while avoiding duplicates
    for substring in a:
        if substring in b and not substring in substringsInCommon:
            substringsInCommon.append(substring)
    return substringsInCommon
