git filter-branch -f --commit-filter '
    if [ "$GIT_AUTHOR_EMAIL" = "kamcpp@gmail.com" ];
    then
            skip_commit "$@";
    else
            git commit-tree "$@";
    fi' HEAD
