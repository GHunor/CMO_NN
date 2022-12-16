function [vq] = CMO_BolkInterpWSmoothStep(xs, vs, xq)
%UNTITLED2 Summary of this function goes here
%   Detailed explanation goes here
    i = 1;
    vq = [];
    for x = xq
        if sum(xs==x)==1
            vq(i) = vs(xs==x, :);
            i = i+1;
            continue;
        end

        H1 = xs(xs<x);
        H2 = vs(xs<x, :);
        x1 = H1(end);
        y1 = H2(end, :);
        H1 = xs(xs>x);
        H2 = vs(xs>x, :);
        x2 = H1(1);
        y2 = H2(1, :);
        for j = 1:length(y1)
            vq(i, j) = SmoothStep(x, x1, x2, y1(j), y2(j));
        end
        i = i+1;
    end
end