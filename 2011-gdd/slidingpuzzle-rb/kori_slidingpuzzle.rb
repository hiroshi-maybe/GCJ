# ruby 1.8.7
# author: kori39@gmail.com
# problem: slidingpuzzle
# google developer day 2011 devquiz

BASE_ORDER = ["1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
EMPTY_CHAR = "0"
WALL_CHAR = "="

CLOSED_LIMIT_NUM = 4000
MOVE_LIMIT = 200

VERTICAL_SCORE = 1
HORIZON_SCORE = 1

#HISTORY_SCORE_WEIGHT = 1
MANHATTAN_SCORE_WEIGHT = 1
SEQUENCE_SCORE_WEIGHT = 1

class GddSlidingpuzzle

  def success(result_history, i)
    p Time.now.strftime("%Y-%m-%d %H:%M:%S").to_s+" "+i.to_s+": success"
    @result_fp.puts result_history
  end

  def failure(i)
    p Time.now.strftime("%Y-%m-%d %H:%M:%S").to_s+" "+i.to_s+": failure"
    @result_fp.puts ""
  end      

  def initialize(file)
    lines = file.readlines
    limits = lines.shift.chomp.split " "

    @l_limit = limits.shift
    @r_limit = limits.shift
    @u_limit = limits.shift
    @d_limit = limits.shift

    @board_num = lines.shift.chomp

    @result_fp = File.open "result."+CLOSED_LIMIT_NUM.to_s, "w"

    lines.each_with_index do |l,i|

      break if i>9

      b = Board.new(i, l.chomp)
      result = b.search

      if result == nil then
        failure i
      else
        success(result.history.to_s, i)
      end

    end

  end

  class Board

    def initialize(id , line)
      @id = id
      dat = line.split ","
      width = dat.shift
      height = dat.shift
      init_seq = dat.shift.split //
      @goal = goal init_seq
      info = BoardInfo.new width, height, init_seq, @goal

      @root = StateNode.new BoardState.new(init_seq, info), nil
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
      @goal_pos = {}
      @goal_cord = {}
      @goal.each_with_index do |e,i|
        @goal_pos[e] = i
        @goal_cord[get_x(i).to_s+get_y(i).to_s]=e
      end
      #@sequence_score_weight = Math::sqrt(@width*@height)
    end

    def get_x (index)
      return index % width
    end
    def get_y (index)
      return index / width
    end

    def get_cord (index)
      return {:x=>get_x(index), :y=>get_y(index)}
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

    attr_reader :width, :height, :seqnum, :goal, :sequence_score_weight, :goal_pos, :goal_cord
  end

  # ボード状態
  class BoardState

    attr_reader :seq, :board_info, :cord

    def initialize(seq, info)
      @seq = seq
      @pos = {}
      @cord = {}
      @seq.each_with_index do |e,i|
        @pos[e] = i
        @cord[info.get_x(i).to_s+info.get_y(i).to_s]=e
      end
      @board_info = info
    end

    def to_s
      str = "@@\n"
      @seq.each_with_index do |n,i|
        str += n
        str += "\n" if (i+1)%@board_info.width==0
      end
      return str
    end

    # パズルが解けた状態
    def complete?()
      return @seq == @board_info.goal
    end

    def move(f)
      result = f.call @pos[EMPTY_CHAR], @board_info.width
      new_pos = result[:position]

#p result[:action]+"->"+new_pos.to_s
      if(new_pos<0 || new_pos>@board_info.seqnum-1 || @seq[new_pos]==WALL_CHAR) then
        raise MoveImpossibleException
      end
      
      seq = Marshal.load(Marshal.dump(@seq))
      seq[@pos[EMPTY_CHAR]],seq[new_pos] = seq[new_pos],seq[@pos[EMPTY_CHAR]]
      return { :state=> BoardState.new(seq, @board_info), :action=> result[:action] }
    end
    private :move

    def u()
      return move(lambda { |empty, width|
        return { :position => empty - width, :action => "U"}})
    end

    def d()
      return move(lambda {|empty, width|
                    return { :position => empty + width, :action => "D"}})
    end

    def r()
      return move(lambda {|empty, width|
                    return { :position => empty + 1, :action => "R"}})
    end

    def l()
      return move(lambda {|empty, width|
                    return { :position => empty - 1, :action => "L"}})
    end

  end

  class SearchManager

    def initialize(root, id)

      @root = root
      @open = []
      @id = id

      # 同じ状態を繰り返さないよう管理
      @closed = Hash.new
      # 未評価のノードを管理
      @open.push root
    end

    def dump(message="")
      filename = "dump/"+sprintf("%03d", @id)

      foo = File.open(filename,'w')

      foo.puts message if message != ""
      foo.puts @open.length.to_s + ":" + @closed.length.to_s
      @open.sort { |a,b|
        a.score <=> b.score
       }.each { |x|
        foo.puts x.state.to_s + ":" + x.history.to_s+":"+x.score.to_s+"("+x.manhattan_score.to_s+","+x.block_score.to_s+","+x.vertical_score.to_s+","+x.horizon_score.to_s+")"
      }
      foo.close
    end

    def move(direc)
      begin

        move_result = direc.call
        history = Marshal.load(Marshal.dump(@current_node.history))
        history.push move_result[:action]
        child_node = StateNode.new move_result[:state], @current_node, history

        if @closed.include? child_node then
          past = @closed[@current_node]
          if @current_node.score < past then
            # better score
            @current_node.append_child child_node
            @closed.delete[@current_node]
          end
        else
          @current_node.append_child child_node
        end

      rescue MoveImpossibleException
      end
    end
    
    def search()

      while !@open.empty? do

        if @closed.length > CLOSED_LIMIT_NUM then
          dump
          return nil
        end

        @current_node = @open.shift
#        @open.delete_at @open.index(@current_node)
        @closed[@current_node] = @current_node.score

        if @current_node.state.complete? then
          dump
          return @current_node
        end
        
        cstate = @current_node.state

        move lambda{cstate.u} if @current_node.history[@current_node.history.length-1] != "D"
        move lambda{cstate.d} if @current_node.history[@current_node.history.length-1] != "U"
        move lambda{cstate.r} if @current_node.history[@current_node.history.length-1] != "L"
        move lambda{cstate.l} if @current_node.history[@current_node.history.length-1] != "R"
        @current_node.children.delete_if{ |n|
          n.history.length > MOVE_LIMIT
        }.each { |m|
          if @open.length==0 || @open[0].score>m.score then
            @open.insert 0, m
          elsif @open[@open.length-1].score<m.score
            @open.push m
          else
            @open.each_with_index do |n,i|
              if n.score >= m.score then
                @open.insert i, m
                break
              end
            end
          end
        }
      end
    end
    
    private :move

  end

  class StateNode

    attr_reader :state, :children, :history, :score, :manhattan_score, :vertical_score, :horizon_score, :block_score

    def initialize(state, parent, history=[])
      @state=state
      @parent=parent
      @children=[]
      @history=history
      @score=get_score
    end

    def append_child(node)
      @children.push node
    end

    def eql?(other)
      return @state.seq.to_s == other.state.seq.to_s
    end

    def hash()
      return @state.seq.to_s.hash
    end

    def manhattan_dis(x1, y1, x2, y2)
      return (x1 - x2).abs + (y1 - y2).abs
    end
    private :manhattan_dis

    def manhattan_dis_score()
      score = 0
      @state.seq.each_with_index do |n,i|

        if n!= WALL_CHAR then
          now_y = @state.board_info.get_y i
          now_x = @state.board_info.get_x i
       
          goal_index = @state.board_info.goal_pos[n]
          goal_y = @state.board_info.get_y goal_index
          goal_x = @state.board_info.get_x goal_index

          score += manhattan_dis now_x, now_y, goal_x, goal_y
        end
      end
      return score
    end

    def vertical_pos_score()
      score = 0
      @state.seq.each_with_index do |n,i|
        break if i>@state.seq.length-2

        if n!=WALL_CHAR then
          # 横に見て右が正しいなら0。そうでないなら2
          seq_neighbor = @state.seq[@state.board_info.neighbor_x(i)]
          goal_neighbor = @state.board_info.goal[@state.board_info.neighbor_x(@state.board_info.goal_pos[n])]
          score += seq_neighbor==goal_neighbor ? 0 : VERTICAL_SCORE
        end
      end
      return score
    end
    def horizon_pos_score()
      score = 0
      @state.seq.each_with_index do |n,i|
        break if i>@state.seq.length-2

        if n!=WALL_CHAR then
          # 縦に見て下が正しいなら0。そうでないなら2
          score += @state.seq[@state.board_info.neighbor_y i]==@state.board_info.goal[@state.board_info.neighbor_y(@state.board_info.goal_pos[n])] ? 0 : HORIZON_SCORE
        end
      end
      return score
    end

    def block_match_score(n,m)

      score = 0
      score_weight = Math::sqrt(n*m)
      (0..@state.board_info.width-n).each do |org_x|
        (0..@state.board_info.height-m).each do |org_y|
          match = true
          (org_x..org_x+n).each do |x|
            (org_y..org_y+m).each do |y|
              match = false if @state.cord[x.to_s+y.to_s] != @state.board_info.goal_cord[x.to_s+y.to_s]
            end
          end
          #x_weight = @state.board_info.width-[org_x,@state.board_info.width-org_x-n].min
          #y_weight = @state.board_info.height-[org_y,@state.board_info.width-org_y-m].min
          score += score_weight if !match
        end
      end
      return score
    end
    
    def get_score()

      if(@state.board_info.goal.length != @state.seq.length) then
        raise "illegal seq_number:"+@state.board_info.goal.length.to_s+":"+@state.seq.length.to_s 
      end
      
      # init -> current
      g = @history.length

      # current -> goal (expectation)
      # heuristic score p(n)+(3)s(n)
      @manhattan_score = manhattan_dis_score
=begin
      @vertical_score = vertical_pos_score
      @horizon_score = horizon_pos_score

      @block_score = 0
      (2..@state.board_info.width).each do |m|
        (2..@state.board_info.height).each do |n|
          @block_score += block_match_score m,n
        end
      end
      @block_score /= @state.board_info.width+@state.board_info.height
#p g.to_s+":"+p.to_s+":"+s.to_s
      #h = MANHATTAN_SCORE_WEIGHT*@manhattan_score + @state.board_info.sequence_score_weight*(SEQUENCE_SCORE_WEIGHT*@vertical_score + SEQUENCE_SCORE_WEIGHT*@horizon_score)
      h = @manhattan_score + @block_score + @vertical_score + @horizon_score
      #h = @block_score
      return (1-g/120)*g+h
=end
      return g+@manhattan_score
    end
    private :get_score

  end

end

class CordianateException < Exception; end

class MoveException < Exception; end
class MoveImpossibleException < MoveException; end

open("./input.dat") do |file|
  puzzle = GddSlidingpuzzle.new(file)
end
