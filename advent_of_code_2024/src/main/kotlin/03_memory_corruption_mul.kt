import java.io.File

fun addUpMuls(inputPath: String): Int {
    var sum = 0
    File(inputPath).forEachLine {
        val regex = Regex("mul\\((\\d{1,3}),(\\d{1,3})\\)")
        val matches = regex.findAll(it)
        sum += matches.map { it.groupValues[1].toInt() * it.groupValues[2].toInt() }.sum()
    }
    return sum
}

fun addUpMulsConsideringDonts(inputPath: String): Int {
    val code = File(inputPath).inputStream().readBytes().toString(Charsets.UTF_8)

    val mulRegex = Regex("mul\\((\\d{1,3}),(\\d{1,3})\\)")
    val muls = mulRegex.findAll(code).toList()

    val doRegex = Regex("do\\(\\)")
    val dos = doRegex.findAll(code).toList()
    val dontRegex = Regex("don't\\(\\)")
    val donts = dontRegex.findAll(code).toList()

    return muls.map { calculateMul(it, dos, donts) }.sum()
}

fun calculateMul(matchRes: MatchResult, dos: List<MatchResult>, donts: List<MatchResult>) : Int {
    val dont = donts.findLast { dont -> dont.range.start < matchRes.range.start }
    if (dont == null){
        return matchRes.groupValues[1].toInt() * matchRes.groupValues[2].toInt()
    }

    val enable = dos.findLast { d -> d.range.start < matchRes.range.start }
    if (enable != null && dont.range.start < enable.range.start){
        return matchRes.groupValues[1].toInt() * matchRes.groupValues[2].toInt()
    }

    return 0
}

fun main(){
    println(addUpMuls("src/main/resources/032.txt"))
    println(addUpMuls("src/main/resources/03.txt"))

    println(addUpMulsConsideringDonts("src/main/resources/032.txt"))
    println(addUpMulsConsideringDonts("src/main/resources/03.txt"))
}