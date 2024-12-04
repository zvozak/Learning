import java.io.File

enum class Direction {
    LEFTDOWN,
    RIGHTDOWN,
}

fun countWordInMatrix(inputPath: String, word: String): Int {
    val lines = File(inputPath).readLines()
    var count = 0

    val lengthOfLines = lines.first().length
    val steps = listOf (
        Pair(0, 1),
        Pair(0, -1),
        Pair(1, 0),
        Pair(1, 1),
        Pair(1, -1),
        Pair(-1, 0),
        Pair(-1, 1),
        Pair(-1, -1))

    for (i in 0..lines.size-1){
        for (j in 0..lengthOfLines-1){
            for (step in steps){
                if (isStartOfWordInMatrixStepping(i, j, word, lines, step)){
                    count++
                }
            }
        }
    }
    return count
}

fun isStartOfWordInMatrixStepping(i: Int, j: Int, word: String, lines: List<String>, step: Pair<Int, Int>): Boolean{
    val lastLineIndex = i + step.first * (word.length-1)
    val lastCharIndex = j + step.second * (word.length-1)
    val lineLen = lines.first().length
    if (lastLineIndex < 0 || lastLineIndex >= lines.size ||
        lastCharIndex < 0 || lastCharIndex >= lineLen){
        return false
    }

    var lineIndex = i
    var charIndex = j
    var wordIndex = 0
    while (wordIndex < word.length && lines[lineIndex][charIndex] == word[wordIndex]){
        wordIndex++
        lineIndex += step.first
        charIndex += step.second
    }

    return wordIndex == word.length
}

fun countXshapedWordInMatrix(inputPath: String, word: String): Int {
    val lines = File(inputPath).readLines()
    var count = 0
    val reversedWord = word.reversed()

    val lengthOfLines = lines.first().length
    val steps = mapOf (
        Pair(Direction.RIGHTDOWN, Pair(1, 1)),
        Pair(Direction.LEFTDOWN, Pair(1, -1)))


    for (i in 0..lines.size-word.length){
        for (j in 0..lengthOfLines-word.length){
            if ((isStartOfWordInMatrixStepping(i, j, word, lines, steps[Direction.RIGHTDOWN]!!) ||
                    isStartOfWordInMatrixStepping(i, j, reversedWord, lines, steps[Direction.RIGHTDOWN]!!)) &&
                (isStartOfWordInMatrixStepping(i, j + word.length-1, word, lines, steps[Direction.LEFTDOWN]!!) ||
                        isStartOfWordInMatrixStepping(i, j + word.length-1, reversedWord, lines, steps[Direction.LEFTDOWN]!!))){
                count++
            }
        }
    }
    return count
}

fun main(){
    println(countWordInMatrix("src/main/resources/042.txt", "XMAS"))
    println(countWordInMatrix("src/main/resources/04.txt", "XMAS"))
    println(countXshapedWordInMatrix("src/main/resources/042.txt", "MAS"))
    println(countXshapedWordInMatrix("src/main/resources/04.txt", "MAS"))
}