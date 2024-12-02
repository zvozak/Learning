import java.io.File
import kotlin.math.abs

fun countSafeReports(inputFilePath: String): Int {
    var countSafe = 0
    File(inputFilePath).forEachLine {
        val levels = it.split(" ").map { it.toInt() }
        if (isSafeReport(levels)){
            countSafe++
        }
    }
    return countSafe
}
fun isLevelDiffSafe(diff: Int, isIncreasing: Boolean): Boolean {
    return (diff != 0) && (abs(diff) <= 3) && ((diff > 0) == isIncreasing)
}

fun getFirstConflict(levels: List<Int>, isIncreasing: Boolean, from: Int = 1): Int {
    if (from >= levels.size){
        return levels.size
    }
    var i = from
    var safe = true
    while (safe && i < levels.size){
        safe = isLevelDiffSafe(levels[i] - levels[i-1], isIncreasing)
        i++
    }

    return if (safe){ i } else { i-1 }
}
fun isSafeStrictlyMonotonicReport(levels: List<Int>, isIncreasing: Boolean): Boolean{
    val firstConflict = getFirstConflict(levels, isIncreasing)

    if (firstConflict >= levels.size-1){
        return true
    }

    if (levels[firstConflict] - levels[firstConflict-1] == 0){
        return getFirstConflict(levels, isIncreasing,firstConflict + 1) == levels.size
    }

    var canSkipPrev = isLevelDiffSafe(levels[firstConflict + 1] - levels[firstConflict], isIncreasing)
    canSkipPrev = canSkipPrev && (firstConflict == 1 || isLevelDiffSafe(levels[firstConflict] - levels[firstConflict-2], isIncreasing))
    val canSkipConflict = isLevelDiffSafe(levels[firstConflict + 1] - levels[firstConflict - 1], isIncreasing)
    val isRemainingWithoutConflict = getFirstConflict(levels, isIncreasing, firstConflict + 2) == levels.size

    return (canSkipConflict || canSkipPrev) && isRemainingWithoutConflict
}

fun isSafeIncreasingReport(levels: List<Int>): Boolean {
    return isSafeStrictlyMonotonicReport(levels, true)
}

fun isSafeDecreasingReport(levels: List<Int>): Boolean {
    return isSafeStrictlyMonotonicReport(levels, false)
}

fun isSafeReport(levels: List<Int>): Boolean {
    if (levels.size < 3){
        return true
    }

    return isSafeDecreasingReport(levels) || isSafeIncreasingReport(levels)
}

fun main(){
    println(countSafeReports("src/main/resources/02.txt"))
}