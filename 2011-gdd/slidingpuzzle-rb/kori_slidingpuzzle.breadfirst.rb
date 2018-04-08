# ruby 1.8.7
# author: kori39@gmail.com
# problem: slidingpuzzle
# google developer day 2011 devquiz

require 'set'

BASE_ORDER = ["1","2","3","4","5","6","7","8","9","A","B","C","D","E","F","G","H","I","J","K","L","M","N","O","P","Q","R","S","T","U","V","W","X","Y","Z"]
EMPTY_CHAR = "0"
WALL_CHAR = "="

class GddSlidingpuzzle
  def initialize(file)
    lines = file.readlines
    limits = lines.shift.chomp.split " "

    @l_limit = limits.shift
    @r_limit = limits.shift
    @u_limit = limits.shift
    @d_limit = limits.shift

    @board_num = lines.shift.chomp

    Board.new lines[0].chomp

#    lines.each do |l|
#      boards = []
#      boards.push Board.new(l.chomp)
#    end      
  end

  class Board

    # ボード形式情報
    class BoardInfo
      def initialize(width, height, init_seq, goal)
        @width = width.to_i
        @height = height.to_i
        @seqnum = init_seq.length
        @goal = goal
      end
      attr_reader :width, :height, :seqnum, :goal
    end

    # ボード状態
    class BoardState

      attr_reader :seq, :history

      def initialize(seq, info, history=[])
        @seq = seq
        @empty_index = @seq.index "0"
        @board_info = info
        @history = history
      end
      
      def score()
        if(@board_info.goal.length != @seq.length) then
          raise "illegal seq_number:"+@board_info.goal.length.to_s+":"+@seq.length.to_s
        end
        
        score = 0;
        @seq.zip(@board_info.goal) do |s,g|
          score = s == g ? score + 1 : score
        end
        return score
      end

      # パズルが解けた状態
      def complete?()
        return score==@board_info.seqnum ? true : false
      end

      def move
        result = yield @empty_index.to_i, @board_info.width
        new_pos = result[:position]
        if(new_pos<0 || new_pos>@board_info.seqnum-1 || @seq[new_pos]==WALL_CHAR) then
          raise MoveImpossibleException
        end
        
        seq = Marshal.load(Marshal.dump(@seq))
        seq[@empty_index],seq[new_pos] = seq[new_pos],seq[@empty_index]
        history = Marshal.load(Marshal.dump(@history))
        return BoardState.new seq, @board_info, history.push(result[:action])
      end
      private :move

      def u()
        return move do |empty, width|
          { :position => empty - width, :action => "U"}
        end
      end

      def d()
        return move do |empty, width|
          { :position => empty + width, :action => "D"}
        end
      end

      def r()
        return move do |empty, width|
          { :position => empty + 1, :action => "R"} 
        end
      end

      def l()
        return move do |empty, width|
          { :position => empty - 1, :action => "L"}    
        end
      end

    end

    def initialize(line)
      dat = line.split ","
      width = dat.shift
      height = dat.shift
      init_seq = dat.shift.split //
      @goal = goal init_seq
      info = BoardInfo.new width, height, init_seq, @goal

      root = StateNode.new BoardState.new(init_seq, info), nil
      manager = SearchManager.new root
      node = root

      result = manager.search
      p result.history
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

  class SearchManager

    def initialize(root)

      @root = root
      @open = []

      # 同じ状態を繰り返さないよう管理
      @closed = Set.new
      # 未評価のノードを管理
      @open.push root
    end

    def move(direc)
      begin
        next_state = direc.call
        child_node = StateNode.new next_state, @current_node
        if !@closed.include? child_node then
          @current_node.append_child child_node
        end
      rescue MoveImpossibleException
      end
    end
    
    def search()

      begin
        @current_node = @open.shift

        if @closed.include? @current_node then
          next
        else
          @closed.add @current_node
        end

        cstate = @current_node.state
        p cstate.history.to_s+":"+cstate.seq.to_s + ":" + cstate.score().to_s
        move lambda{||cstate.u}
        move lambda{||cstate.d}
        move lambda{||cstate.r}
        move lambda{||cstate.l}

        strategy = BreadFirstStrategy.new
        strategy.push @current_node, @open
      end until @current_node.state.complete? || @open.empty?

      return @current_node
    end
    
    private :move

  end

  class BreadFirstStrategy
    def push(current_node, open)
      current_node.children.each do |child|
        open.push child
      end
    end
  end

  class StateNode

    attr_reader :state, :children
    attr_accessor :dead

    def initialize(state, parent)
      @state=state
      @parent=parent
      @children=[]
      @dead=false
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

=begin
    def next_node()

      # 子がdeadなら削除
      @children.delete_if do |x| 
        x.dead
      end

      # 子無しでここから先探索不可能な場合は親にさかのぼる
      if @children.length == 0 then
        @dead=true
p "dead"
        return @parent.parent
      end

      # to be enhanced
      # 残り操作が多い物を優先するなど
      max_child = @children.max do |a, b|
        a.state.score <=> b.state.score
      end

      # 親がいてかつ子でスコアが下がった場合は、親へ戻る
      return @parent != nil && max_child.state.score < @parent.state.score ? @parent : max_child

    end
=end
  end

end


class MoveException < Exception; end
class MoveImpossibleException < MoveException; end

open("./input.dat") do |file|
  puzzle = GddSlidingpuzzle.new(file)
end

