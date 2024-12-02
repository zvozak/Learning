import java.io.File
import java.util.PriorityQueue
import kotlin.math.abs

fun getDistance(inputFilePath: String): Int {
    val listLeft = PriorityQueue<Int>()
    val listRight = PriorityQueue<Int>()

    File(inputFilePath).forEachLine {
        val line = it.split("   ")
        listLeft.add(line[0].toInt())
        listRight.add(line[1].toInt())
    }

    var distance = 0
    while (!listLeft.isEmpty()){
        distance += abs(listLeft.poll() - listRight.poll())
    }

    return distance
}

fun getSimilarityScore(inputFilePath: String): Int {
    val mapRight = mutableMapOf<Int, Int>()
    val mapLeft = mutableMapOf<Int, Int>()

    File(inputFilePath).forEachLine {
        val line = it.split("   ").map { it.toInt() }

        mapLeft.getOrPut(line[0]) {
            0
        }
        mapLeft[line[0]] = mapLeft[line[0]]!! + 1

        mapRight.getOrPut(line[1]) {
            0
        }
        mapRight[line[1]] = mapRight[line[1]]!! + 1
    }

    var similarity = 0
    for ((k, v) in mapLeft) {
        if (mapRight.containsKey(k)) {
            similarity += mapRight[k]!! * v * k
        }
    }
    return similarity
}

fun main(){
    println(getDistance("src/main/resources/01.txt"))
    println(getSimilarityScore("src/main/resources/01.txt"))
}