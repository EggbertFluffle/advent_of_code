const std = @import("std");

const allocator = std.heap.page_allocator;

const Tile = struct {
    top: u32,
    left: u32,
    right: u32,
    bottom: u32,
    
    id: i32,
    
    pub fn init(line: []u8) Tile {
        var it = std.mem.splitAny(u8, line, " ");
        const id = std.fmt.parseInt(i32, it.next().?, 10) catch {
            std.process.abort();
        };

        var lines: [10][10]u8 = undefined;

        for(0..1) |i| {
            // const l = it.next().?;
            // for(0..l.len) |p| {
            //     lines[i][p] = l[p];
            // }
            std.mem.copyForwards(u8, &lines[i], it.next().?);
        }

        var top: u32 = 0;
        var left: u32 = 0;
        var right: u32 = 0;
        var bottom: u32 = 0;

        for(0..10) |i| {
            top    |= if (lines[0][i] == '#') (@as(u32, 1) << @as(u5, @intCast(i))) else 0;
            bottom |= if (lines[9][i] == '#') (@as(u32, 1) << @as(u5, @intCast(i))) else 0;
            left   |= if (lines[i][0] == '#') (@as(u32, 1) << @as(u5, @intCast(i))) else 0;
            right  |= if (lines[i][9] == '#') (@as(u32, 1) << @as(u5, @intCast(i))) else 0;
        }

        return .{
            .id = id,
            .top = top,
            .bottom = bottom,
            .left = left,
            .right = right,
        };
    }

    pub fn contians(self: *Tile, border: u32) bool {
        return self.top == border or
            self.bottom == border or
            self.left == border or
            self.right == border;
    }
};

pub fn main() !void {
    // const input = try read_lines("input.txt");
    const input = try read_tiles("test.txt");
    
}

pub fn read_tiles(file_name: []const u8) !std.ArrayList(Tile) {
    var out: std.ArrayList(Tile) = try .initCapacity(allocator, 16);
    const file = std.fs.cwd().openFile(file_name, .{ .mode = .read_only }) catch |err| {
        std.debug.print("unable to open file at {s}", .{file_name});
        return err;
    };

    var buf: [1024 * 1024]u8 = undefined;
    var reader = file.reader(&buf);

    while(true) {
        const line = reader.interface.takeDelimiterExclusive('\n') catch {
            return out;
        };
        try out.append(allocator, Tile.init(line));
    }
}
