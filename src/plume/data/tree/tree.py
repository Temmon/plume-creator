'''
Created on 13 february 2016

@author:  Cyril Jacquet
'''


import sqlite3
from .db_tree import DbTree
from .db_paper import DbPaper


class Tree:
    '''
    Tree
    '''

    def __init__(self, sql_db: sqlite3.Connection, table_name: str, id_name: str):
        '''
        Constructor
        :type table_name: str
        :type sql_db: sqlite3.Connection
        :type id_name: str
        '''

        self.table_name = table_name
        self.id_name = id_name
        self.sql_db = sql_db

        tree = DbTree(sql_db, table_name, id_name, True)
        tree.renum_all()

    def get_all(self)-> list:
        '''
        function:: get_all()
        :return [{"name", value},...}
        '''
        tree = DbTree(self.sql_db, self.table_name, self.id_name, False)
        return tree.get_all()

    def get_all_headers(self)-> list:
        '''
        function:: get_all_headers()
        '''
        tree = DbTree(self.sql_db, self.table_name, self.id_name, False)
        return tree.get_all_headers()

    def get_content(self, paper_id: int):
        '''
        function:: get_content(id: int)
        :param paper_id: int:
        '''
        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, False)
        return paper.get("m_content")

    def set_content(self, paper_id: int, value):
        '''
        function:: set_content(id: int, value)
        :param paper_id: int:
        :param value:
        '''
        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, True)
        paper.set("m_content", value)

    def get_title(self, paper_id: int):
        '''
        function:: get_title(id: int)
        :param paper_id: int:
        '''
        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, False)
        return str(paper.get("t_title"))

    def set_title(self, paper_id: int, value: str):
        '''
        function:: set_title(id: int)
        :param value:
        :param paper_id: int:
        '''
        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, True)
        paper.set("t_title", value)

    def add_new_child_papers(self, parent_id: int, number: int):
        '''
        function:: add_new_child_papers(parent_id: int, number: int)
        :param parent_id: int:
        :param number: int:
        '''
        return self._add_new_child_papers(parent_id, number, True)

    def add_new_papers_by(self, paper_id: int, number: int):
        '''
        function:: add_new_papers_by(parent_id: int, number: int)
        :param paper_id: int:
        :param number: int:
        '''
        return self._add_new_papers_by(paper_id, number, True)

    def move_papers_as_child_of(self, paper_id_list, dest_parent_id: int):
        '''
        function:: move_papers_as_child_of(paper_id_list, dest_parent_id: int)
        :param paper_id_list:
        :param dest_parent_id: int:
        '''
        return self._move_papers_as_child_of(paper_id_list, dest_parent_id, True)

    def move_papers_above(self, paper_id_list, dest_id: int):
        '''
        function:: move_papers_above(paper_id_list, dest_id: int)
        :param paper_id_list:
        :param dest_id: int:
        '''

        return self._move_papers_above(paper_id_list, dest_id, True)

    def move_papers_below(self, paper_id_list, dest_id: int):
        '''
        function:: move_papers_below(paper_id_list, dest_id: int)
        :param paper_id_list:
        :param dest_id: int:
        '''

        return self._move_papers_below(paper_id_list, dest_id, True)

    def _add_new_child_papers(self, parent_id: int, number: int, commit: bool):
        '''
        function:: _add_new_child_papers(parent_id: int, number: int, commit: bool)
        :param parent_id: int:
        :param number: int:
        :param commit: bool:
        '''

        new_id_list = []
        for i in range(number):
            paper = DbPaper(self.sql_db, self.table_name, self.id_name,  -1, False)
            new_id_list.append(paper.add())
        self._move_papers_as_child_of(new_id_list, parent_id, False)
        if commit:
            self.sql_db.commit()

        return new_id_list

    def _add_new_papers_by(self, paper_id: int, number: int, commit: bool):
        '''
        function:: _add_new_papers_by(parent_id: int, number: int, commit: bool)
        :param paper_id: int:
        :param number: int:
        :param commit: bool:
        '''

        new_id_list = []
        for i in range(number):
            paper = DbPaper(self.sql_db, self.table_name, self.id_name,  -1, False)
            new_id_list.append(paper.add())
        self._move_papers_below(new_id_list, paper_id, False)
        if commit:
            self.sql_db.commit()

        return new_id_list

    def _move_papers_as_child_of(self, paper_id_list, dest_parent_id: int, commit: bool):
        '''
        function:: _move_papers_as_child_of(paper_id_list, dest_parent_id: int, commit: bool)
        :param paper_id_list:
        :param dest_parent_id: int:
        :param commit: bool:
        '''

        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  dest_parent_id, False)
        tree = DbTree(self.sql_db, self.table_name, self.id_name, False)
        child_id_list = paper.list_children()
        dest_parent_indent = paper.indent
        if not child_id_list:
            tree.move_list(paper_id_list, dest_parent_id)
        elif child_id_list:
            self._move_papers_below(paper_id_list, child_id_list[-1], False)
        for paper_id in paper_id_list:
            child_paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, False)
            child_paper.indent = dest_parent_indent + 1

        tree.renum_all()

        if commit:
            self.sql_db.commit()

    def _move_papers_above(self, paper_id_list, dest_id: int, commit: bool):
        '''
        function:: _move_papers_above(paper_id_list, dest_id: int, commit: bool)
        :param paper_id_list:
        :param dest_id: int:
        :param commit: bool:
        '''
        tree = DbTree(self.sql_db, self.table_name, self.id_name, False)
        paper_above = tree.get_paper_above(dest_id)
        tree.move_list(paper_id_list, paper_above)

        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  dest_id, False)
        dest_indent = paper.indent
        for paper_id in paper_id_list:
            child_paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, False)
            child_paper.indent = dest_indent

        tree.renum_all()

        if commit:
            self.sql_db.commit()

    def _move_papers_below(self, paper_id_list, dest_id: int, commit: bool):
        '''
        function:: _move_papers_below(paper_id_list, dest_id: int, commit: bool)
        :param paper_id_list:
        :param dest_id: int:
        :param commit: bool:
        '''
        tree = DbTree(self.sql_db, self.table_name, self.id_name, False)
        tree.move_list(paper_id_list, dest_id)

        paper = DbPaper(self.sql_db, self.table_name, self.id_name,  dest_id, False)
        dest_indent = paper.indent
        for paper_id in paper_id_list:
            child_paper = DbPaper(self.sql_db, self.table_name, self.id_name,  paper_id, False)
            child_paper.indent = dest_indent

        tree.renum_all()

        if commit:
            self.sql_db.commit()
