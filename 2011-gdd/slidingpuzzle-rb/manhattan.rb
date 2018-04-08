# ruby 1.8.7
# author: kori39@gmail.com
# problem: slidingpuzzle
# google developer day 2011 devquiz

BASE_ORDER = ["1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
EMPTY_CHAR = "0"
WALL_CHAR = "="

CLOSED_LIMIT_NUM = 10000
MOVE_LIMIT = 1200

VERTICAL_SCORE = 1
HORIZON_SCORE = 1

#HISTORY_SCORE_WEIGHT = 1
MANHATTAN_SCORE_WEIGHT = 1
SEQUENCE_SCORE_WEIGHT = 1


class Board

  attr_reader :info

  def initialize(id , line)
    @id = id
    dat = line.split ","
    width = dat.shift
    height = dat.shift
    init_seq = dat.shift.split //
      @goal = goal init_seq
p @goal
    @info = BoardInfo.new width, height, init_seq, @goal

#    @root = StateNode.new BoardState.new(init_seq, info), nil
  end

  def search
    manager = SearchManager.new @root, @id
    return  manager.search
  end
  
  def goal(seq)
    goal_seq = []
    seq.length.times do |i|
      if (WALL_CHAR == seq[i]) then
        goal_seq.push WALL_CHAR
      elsif (i == seq.length-1) then
        goal_seq.push EMPTY_CHAR
      else
        goal_seq.push BASE_ORDER[i]
      end
    end
    return goal_seq
  end
  
end

# ボード形式情報
class BoardInfo
  def initialize(width, height, init_seq, goal)
    @width = width.to_i
    @height = height.to_i
    @seqnum = init_seq.length
    @goal = goal
    @sequence_score_weight = Math::sqrt(@width*@height)
  end

  def get_x (index)
    return index % width
  end
  def get_y (index)
    return index / width
  end

  def valid(x,y)
    raise CordinateException if x>@width-1 || y>@height-1 || x<0 || y<0
  end

  def neighbor(index, f)
    x = get_x index
    y = get_y index
    valid x,y

    result = f.call x,y
    x = result[:x]
    y = result[:y]

    return index_at x,y      
  end
  private :neighbor

  def neighbor_x (index)
    return neighbor(index, lambda {|x,y|
                      if x==@width-1 then
                        x = 0
                        y = y==@height-1 ? 0 : y+1
                      else
                        x += 1
                      end
                      return{:x=>x, :y=>y}
                    })
  end

  def neighbor_y (index)
    return neighbor(index, lambda {|x,y|
                      if y==@height-1 then
                        y = 0
                        x = x==@width-1 ? 0 : x+1
                      else
                        y += 1
                      end
                      return {:x=>x, :y=>y}             
                    })
  end

  def index_at (x,y)
    return @width * y +x
  end

  def manhattan_dis(x1, y1, x2, y2)
    return (x1 - x2).abs + (y1 - y2).abs
  end

  def manhattan_dis_score(seq)
    score = 0
    seq.each_with_index do |n,i|
      now_y = get_y i
      now_x = get_x i
      
      goal_index = @goal.index n
      goal_y = get_y goal_index
      goal_x = get_x goal_index

md = manhattan_dis now_x, now_y, goal_x, goal_y
p n+"("+now_x.to_s+","+now_y.to_s+") ("+goal_x.to_s+","+goal_y.to_s+") "+md.to_s

      score += md
    end
    return score
  end


  attr_reader :width, :height, :seqnum, :goal, :sequence_score_weight
end

seq = "123=506879BCAEFGHIJKLMNOPDRSQT"

board = Board.new "x", "6,5,238=I67E9MBC1AF05HJKRLNGPDQSTO"

input = seq.split //
p seq
p board.info.manhattan_dis_score input
